#import "@preview/cuti:0.3.0": show-cn-fakebold
#import "unit.typ": *

#let font-size = (
  初号: 42pt,
  小初: 36pt,
  一号: 26pt,
  小一: 24pt,
  二号: 22pt,
  小二: 18pt,
  三号: 16pt,
  小三: 15pt,
  四号: 14pt,
  中四: 13pt,
  小四: 12pt,
  五号: 10.5pt,
  小五: 9pt,
  六号: 7.5pt,
  小六: 6.5pt,
  七号: 5.5pt,
  小七: 5pt,
)

#let font-family = (
  // 宋体，属于「有衬线字体」，一般可以等同于英文中的 Serif Font
  // 这一行分别是「新罗马体（有衬线英文字体）」、「思源宋体（简体）」、「思源宋体」、「宋体（Windows）」、「宋体（MacOS）」
  SongTi: (
    (name: "Times New Roman", covers: "latin-in-cjk"),
    "Source Han Serif SC",
    "Source Han Serif",
    "Noto Serif CJK SC",
    "SimSun",
    "Songti SC",
    "STSongti",
  ),
  // 黑体，属于「无衬线字体」，一般可以等同于英文中的 Sans Serif Font
  // 这一行分别是「Arial（无衬线英文字体）」、「思源黑体（简体）」、「思源黑体」、「黑体（Windows）」、「黑体（MacOS）」
  HeiTi: (
    (name: "Arial", covers: "latin-in-cjk"),
    "Source Han Sans SC",
    "Source Han Sans",
    "Noto Sans CJK SC",
    "SimHei",
    "Heiti SC",
    "STHeiti",
  ),
  // 楷体
  KaiTi: ((name: "Times New Roman", covers: "latin-in-cjk"), "KaiTi", "Kaiti SC", "STKaiti", "FZKai-Z03S"),
  // 仿宋
  FangSong: (
    (name: "Times New Roman", covers: "latin-in-cjk"),
    "FangSong",
    "FangSong SC",
    "STFangSong",
    "FZFangSong-Z02S",
  ),
  // 等宽字体，用于代码块环境，一般可以等同于英文中的 Monospaced Font
  // 这一行分别是「Courier New（Windows 等宽英文字体）」、「思源等宽黑体（简体）」、「思源等宽黑体」、「黑体（Windows）」、「黑体（MacOS）」
  Mono: (
    (name: "Courier New", covers: "latin-in-cjk"),
    (name: "Menlo", covers: "latin-in-cjk"),
    (name: "IBM Plex Mono", covers: "latin-in-cjk"),
    "Source Han Sans HW SC",
    "Source Han Sans HW",
    "Noto Sans Mono CJK SC",
    "SimHei",
    "Heiti SC",
    "STHeiti",
  ),
)

#let defineConfig(
  lang: "zh",
  region: "cn",
  doctype: "bachelor",
  margin-style: "narrow",
  doc,
) = {
  show: show-cn-fakebold

  let _page_margin_style = ("narrow", "middle", "normal", "wide")

  assert(
    _page_margin_style.contains(margin-style),
    message: "Unsupported margin style, only support: " + _page_margin_style.join(", "),
  )

  let _page_margin = if margin-style == "narrow" {
    1.27cm
  } else if margin-style == "middle" {
    (x: 1.91cm, y: 2.54cm)
  } else if margin-style == "wide" {
    (x: 5.08cm, y: 2.54cm)
  } else if margin-style == "normal" {
    (x: 3.18cm, y: 2.54cm)
  }

  set page(paper: "a4", margin: _page_margin)

  let _support_lang = ("zh", "en")

  assert(
    _support_lang.contains(lang),
    message: "Unsupported language, only support: " + _support_lang.join(", "),
  )

  set text(lang: lang, region: region)

  let _support_doctype = ("bachelor", "master", "doctor")

  assert(
    _support_doctype.contains(doctype),
    message: "Unsupported doctype, only support: " + _support_doctype.join(", "),
  )

  doc
}
