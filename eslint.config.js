// @ts-check
import antfu from '@antfu/eslint-config'

export default antfu({
  formatters: true,

  markdown: false,
  jsonc: false,

  ignores: [
    '**/pyproject.toml',
    '**/zip.mjs',
    '.github/workflows/*.yml',
  ],
})
