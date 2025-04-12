/* eslint-disable no-console */
import fs from 'node:fs'
import archiver from 'archiver'

const output = fs.createWriteStream('hw.zip')
const archive = archiver('zip', { zlib: { level: 9 } })

const archiveFile = path => archive.file(path, { name: path })
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

void ['LICENSE', 'README.md', 'xmake.lua', 'doxyfile', 'justfile'].forEach(archiveFile)

void ['src', 'dist', 'docs'].forEach(archiveDir)

archive.finalize()
