/// This is a draft of a dotenv implementation in Typst
///
/// Don't use this file and please refer to the repo for more information
///
/// repo: https://github.com/chillcicada/typst-dotenv
#let env_load(path) = {
  let obj = (:)

  for item in read(path).split(regex("#.*\r?\n|\r?\n")).filter(it => it.trim() != "").map(line => {
    let parts = line.split("=")
    let key = parts.at(0).trim()
    if (key != "") {
      if (parts.len() > 1) {
        (key, parts.at(1).trim())
      } else {
        (key, "")
      }
    }
  }).dedup() {
    obj.insert(item.at(0), item.at(1))
  }

  obj
}

/// load the `.env` file in the root by default
#let env = env_load("/.env")
