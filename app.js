const express = require('express')
const bodyParser = require('body-parser');
const fs = require('fs');
const cmd = require('node-cmd');
const Rx = require('rxjs/Rx')
const rimraf = require('rimraf');

const app = express();
app.use(bodyParser.text());

const arduinoMakeFolder = 'sketchbook/';

/**
 * Writes the arduino code
 */
let writeArduinoCodeFileAndMakeFile = (code, board) => {

    let folderCreated = Date.now() + '_' + Math.floor(Math.random() * 400000) ;
    let filePath = arduinoMakeFolder + folderCreated;

    let makeDirectoryFunc = Rx.Observable.bindNodeCallback(fs.mkdir);
    let copyFileFunc = Rx.Observable.bindNodeCallback(fs.copyFile);
    let createFile = Rx.Observable.bindNodeCallback(fs.writeFile);

    return makeDirectoryFunc(filePath)
        .flatMap(() => copyFileFunc('sketchbook/Makefile_' + board, filePath + '/Makefile'))
        .flatMap(() => createFile(filePath + '/sketch.ino', code))
        .map(() => folderCreated);

};

app.post('/upload-code/:board', (req, res) => {

    let getCommand = Rx.Observable.bindNodeCallback(cmd.get);
    let deleteDirectory = Rx.Observable.bindNodeCallback(rimraf);
    let board = req.params['board'];

    writeArduinoCodeFileAndMakeFile(req.body, board)
        .take(1)
        .flatMap(folderCreatedName =>  {
               return getCommand('cd ' + arduinoMakeFolder + folderCreatedName + ' && find . -exec touch {} \\; && make ')
                   .map(() => folderCreatedName)
        })
        .flatMap(folderCreatedName => {
            res.writeHead(200, {
                "Content-Type": "application/octet-stream",
                "Content-Disposition": "attachment; filename=sketchcode.hex"
            });
            fs.createReadStream(arduinoMakeFolder + folderCreatedName + '/build-' +board + '/' + folderCreatedName + '.hex').pipe(res);

            return deleteDirectory(arduinoMakeFolder + folderCreatedName)
                .map(() => undefined)
        })
        .catch(err =>  Rx.Observable.of(err))
        .subscribe(err => err ?  console.error('ERROR', err) : console.log('SUCCESS'));
});

app.listen(1337, () => console.log('Example app listening on port 1337!'))