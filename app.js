const Promise = require('bluebird');
const express = require('express');
const bodyParser = require('body-parser');
const cmd = Promise.promisifyAll(require('node-cmd'));
const rimraf = Promise.promisify(require('rimraf'));
const fs = Promise.promisifyAll(require('fs'));

const app = express();
app.use(bodyParser.text());

const arduinoMakeFolder = 'sketchbook/';

/**
 * Writes the arduino code
 */
const writeArduinoCodeFileAndMakeFile = async (code, board) => {
  const folderCreated = Date.now() + '_' + Math.floor(Math.random() * 400000);
  const filePath = arduinoMakeFolder + folderCreated;

  await fs.mkdirAsync(filePath);

  await fs.chmodAsync(filePath, '777');

  await fs.copyFileAsync(
    'sketchbook/Makefile_' + board,
    filePath + '/Makefile'
  );

  await fs.writeFileAsync(filePath + '/sketch.ino', code);

  await fs.copyFileAsync(
    'sketchbook/Makefile_' + board,
    filePath + '/Makefile'
  );

  return folderCreated;
};

app.post('/upload-code/:board', async (req, res) => {
  try {
    let board = req.params['board'];

    const folderCreatedName = await writeArduinoCodeFileAndMakeFile(
      req.body,
      board
    );

    await cmd.getAsync(
      'cd ' +
        arduinoMakeFolder +
        folderCreatedName +
        ' && find . -exec touch {} \\; && make '
    );
    res.writeHead(200, {
      'Content-Type': 'application/octet-stream',
      'Content-Disposition': 'attachment; filename=sketchcode.hex'
    });
    fs.createReadStream(
      arduinoMakeFolder +
        folderCreatedName +
        '/build-' +
        board +
        '/' +
        folderCreatedName +
        '.hex'
    ).pipe(res);

    await rimraf(arduinoMakeFolder + folderCreatedName);
  } catch (err) {
    res.send(JSON.stringify({ error: err }));
    console.error('ERROR COMPILING: ' + err);
  }
});

app.get('/', (req, res) => {
  res.send('NoDe cOmpILes aRduiNo seRveR working');
});

app.listen(1338, () => console.log('Example app listening on port 1338!'));
