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
    let chmodFolder = Rx.Observable.bindNodeCallback(fs.chmod);

    return makeDirectoryFunc(filePath)
        .flatMap(() => chmodFolder(filePath, '777'))
        .flatMap(() => createFile(filePath + '/sketch.ino', code))
        .flatMap(() => copyFileFunc('sketchbook/Makefile_' + board, filePath + '/Makefile'))
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
        .subscribe(err => {
            if (!res.headerSent && err) {
                res.send(JSON.stringify({'error': err}));
                console.error("ERROR COMPILING: " + err);
            }

        });
});

app.get('/', (req, res) => {
    res.send('NoDe cOmpILes aRduiNo seRveR')
})

app.listen(1338, () => console.log('Example app listening on port 1338!'))