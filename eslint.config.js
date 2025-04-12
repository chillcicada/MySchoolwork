// @ts-check
import antfu from '@antfu/eslint-config'

export default antfu({
  formatters: true,

  markdown: false,
  jsonc: false,

  ignores: [
    '**/*.md',
    '**/pyproject.toml',
    '.github/workflows/*.yml',
  ],
})
