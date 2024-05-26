#let conf(
  quarto: false,
  title: none,
  authors: (),
  doc,
) = {
  set text(
    weight: "regular",
    font: ("Times New Roman", "LXGW WenKai"),
    size: 11pt,
  )

  set par(justify: true)

  show heading.where(
    level: 1,
  ): it => block(
    align(
      center,
      text(
        14pt,
        weight: "bold",
        smallcaps(it.body),
      )
    )
  )

  show heading.where(
    level: 2
  ): it => box(
    text(
      12pt,
      weight: "regular",
      it.body + [:],
    )
  )

  set align(center)
  text(18pt, title)

  let count = calc.min(authors.len(), 3)
  grid(
    columns: (1fr,) * count,
    row-gutter: 24pt,
    ..authors.map(author => [
      #author.name \
      #author.studentID \
      #link("mailto:" + author.email)
    ])
  )

  if (quarto) {
    show raw: it => block(
      fill: rgb("#eeeeee"),
      inset: 8pt,
      radius: 5pt,
      text(fill: rgb("#111111"), it),
      width: 100%,
    )
  }

  set align(left)
  doc
}
