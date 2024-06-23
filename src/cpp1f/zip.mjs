import fs from 'node:fs'
import archiver from 'archiver'

const output = fs.createWriteStream('hw.zip')
const archive = archiver('zip', { zlib: { level: 9 } })

const archiveFile = path => archive.file(path, { name: path })
const archiveDir = path => archive.directory(path, path)

output.on('close', () => {
  console.log(archive.pointer() + ' total bytes')
  console.log('archiver has been finalized and the output file descriptor has closed.')
})

output.on('end', () => { console.log('Data has been drained') })

archive.on('warning', err => console.warn(err))

archive.pipe(output)

archiveFile('LICENSE')
archiveFile('README.md')
archiveFile('xmake.lua')
archiveFile('doxyfile')
archiveFile('justfile')

archiveDir('src')
archiveDir('dist')
archiveDir('docs')

archive.finalize()
