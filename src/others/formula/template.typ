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
  SongTi: (
    (name: "Times New Roman", covers: "latin-in-cjk"),
    "NSimSun",
  ),
  HeiTi: (
    (name: "Arial", covers: "latin-in-cjk"),
    "SimHei",
  ),
  // 楷体
  KaiTi: ((name: "Times New Roman", covers: "latin-in-cjk"), "KaiTi"),
  // 仿宋
  FangSong: (
    (name: "Times New Roman", covers: "latin-in-cjk"),
  ),
  Mono: (
    (name: "Courier New", covers: "latin-in-cjk"),
    "SimHei",
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

  set text(lang: lang, region: region, font: font-family.SongTi)

  let _support_doctype = ("bachelor", "master", "doctor")

  assert(
    _support_doctype.contains(doctype),
    message: "Unsupported doctype, only support: " + _support_doctype.join(", "),
  )

  doc
}
