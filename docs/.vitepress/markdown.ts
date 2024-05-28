import { readFileSync } from 'node:fs'
import { join } from 'node:path'
import type { MarkdownOptions } from 'vitepress'
import { transformerTwoslash } from '@shikijs/vitepress-twoslash'

const j = (str: `${string}.tmLanguage.json`) => JSON.parse(readFileSync(join(__dirname, 'assets', str), 'utf8'))

/**
 * @description: use fortran-lang's highlight syntax
 * @see: https://github.com/fortran-lang/vscode-fortran-support/tree/main/syntaxes/
 */
const fortran77 = j('fortran_fixed-form.tmLanguage.json')
const fortran90 = j('fortran_free-form.tmLanguage.json')
const openmpLang = j('openmp_lang.tmLanguage.json')
const openaccLang = j('openacc_lang.tmLanguage.json')

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
  codeTransformers: [transformerTwoslash()],
} satisfies MarkdownOptions

export default markdown
