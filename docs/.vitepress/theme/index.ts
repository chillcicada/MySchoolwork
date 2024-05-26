// https://vitepress.dev/guide/custom-theme
import { h } from 'vue'
import type { EnhanceAppContext, Theme } from 'vitepress'
import DefaultTheme from 'vitepress/theme'
import './style.css'
import TwoslashFloatingVue from 'vitepress-plugin-twoslash/client'
import 'vitepress-plugin-twoslash/style.css'

export default {
  extends: DefaultTheme,
  Layout: () => {
    return h(DefaultTheme.Layout, null, {
      // https://vitepress.dev/guide/extending-default-theme#layout-slots
    })
  },
  // app, router, siteData
  enhanceApp({ app }: EnhanceAppContext) {
    app.use(TwoslashFloatingVue as unknown as any)
  },
} satisfies Theme
