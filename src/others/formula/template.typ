#import "@preview/cuti:0.3.0": show-cn-fakebold
#import "unit.typ": *

#let defineConfig(
  lang: "zh",
  region: "cn",
  doctype: "bachelor",
  narrow-margin: true,
  doc,
) = {
  show: show-cn-fakebold

  let _page_margin = if narrow-margin { 1.27cm } else { 2.54cm }

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
