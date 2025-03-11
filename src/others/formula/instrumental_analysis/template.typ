#import "@preview/cuti:0.3.0": show-cn-fakebold
#import "../unit.typ": *

#let defineConfig(
  doc,
) = {
  show: show-cn-fakebold

  set page(paper: "a4", margin: 1.27cm)
  set text(lang: "zh", region: "cn")

  doc
}
