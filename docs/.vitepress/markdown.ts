import { readFileSync } from 'node:fs'
import { join } from 'node:path'
import type { MarkdownOptions } from 'vitepress'
import { transformerTwoslash } from 'vitepress-plugin-twoslash'

/**
 * @description: use fortran-lang's highlight syntax
 * @see: https://github.com/fortran-lang/vscode-fortran-support/tree/main/syntaxes/
 */
const fortran77 = JSON.parse(readFileSync(join(__dirname, './assets/fortran_fixed-form.tmLanguage.json'), 'utf8'))
const fortran90 = JSON.parse(readFileSync(join(__dirname, './assets/fortran_free-form.tmLanguage.json'), 'utf8'))
const openmpLang = JSON.parse(readFileSync(join(__dirname, './assets/openmp_lang.json'), 'utf8'))
const openaccLang = JSON.parse(readFileSync(join(__dirname, './assets/openacc_lang.json'), 'utf8'))

const markdown: MarkdownOptions = {
  math: true,
  languages: [
    {
      ...fortran90,
      aliases: ['fortran'],
    },
    fortran77,
    openaccLang,
    openmpLang,
  ],
  // TODO
  codeTransformers: [transformerTwoslash() as any],
}

export default markdown
