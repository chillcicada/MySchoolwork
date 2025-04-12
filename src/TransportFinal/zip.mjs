/* eslint-disable no-console */
import fs from 'node:fs'
import archiver from 'archiver'

const output = fs.createWriteStream('hw.zip')
const archive = archiver('zip', { zlib: { level: 9 } })

const archiveFileAs = ([path, name]) => archive.file(path, { name })
const archiveFile = path => archiveFileAs([path, path])
const archiveDir = path => archive.directory(path, path)

output.on('close', () => {
  console.log(`${archive.pointer()} total bytes`)
  console.log('archiver has been finalized and the output file descriptor has closed.')
})

output.on('end', () => {
  console.log('Data has been drained')
})

archive.on('warning', err => console.warn(err))

archive.pipe(output)

void ['report.pdf'].forEach(archiveFile)

void [
  ['src/__init__.py', 'main.py'],
  ['src/solution.cpp', 'main.cpp'],
  ['src/solution.ipynb', 'main.ipynb'],
  ['build/windows/x64/release/main.exe', 'main.exe'],
].forEach(archiveFileAs)

void ['_img', 'assets'].forEach(archiveDir)

archive.finalize()
