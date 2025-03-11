#import "@preview/cuti:0.3.0": show-cn-fakebold

#let defineConfig(
  doc,
) = {
  show: show-cn-fakebold

  set page(paper: "a4", margin: 1.27cm)
  set text(lang: "zh", region: "cn")

  show heading.where(level: 1): it => {
    align(center, it)
  }

  doc
}
