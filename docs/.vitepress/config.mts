import { defineConfig } from 'vitepress'

import nav from './nav'
import sidebar from './sidebar'
import markdown from './markdown'
import { blog, ncm } from './icons'

// https://vitepress.dev/reference/site-config
export default defineConfig({
  title: 'Cc\'s Schoolwork',
  description: 'A Simple Site',
  themeConfig: {
    // https://vitepress.dev/reference/default-theme-config
    nav,

    sidebar,

    socialLinks: [
      { icon: 'github', link: 'https://github.com/chillcicada/MySchoolwork' },
      { icon: { svg: ncm }, link: 'https://music.163.com/#/user/home?id=1403030074' },
      { icon: { svg: blog }, link: 'https://chillcicada.com' },
    ],

    editLink: {
      pattern: 'https://github.com/chillcicada/MySchoolwork/issues/new',
      text: '勘误',
    },

    outline: 'deep',

    docFooter: {
      prev: '上一页',
      next: '下一页',
    },

    lastUpdated: {
      text: '最后更新于',
      formatOptions: {
        dateStyle: 'short',
        timeStyle: 'medium',
      },
    },

    footer: {
      message: '基于 CC BY-NC-SA 4.0 许可发布',
      copyright: `版权所有 © 2023-${new Date().getFullYear()} <a href="https://github.com/chillcicada" target="_blank" class="copyright-author">ChillCicada</a>`,
    },

    search: {
      provider: 'local',
    },
  },

  markdown,
})
