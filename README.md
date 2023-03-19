# gh-puller

> ⚠️ This is highly experimental project that demonstrates the usage of Scala Native with Scala CLI

- [Oto Brglez](https://twitter.com/otobrglez)

## Development

The easies way to get started with this project is to install [`nix-shell`][nix-shell] and then install [Scala CLI][scala-cli] and other dependencies, such as [`libcurl`][libcurl] with it.

```bash
nix-shell --pure ./shell.nix
make clean all
```

Or with `scala-cli`:

```bash
scala-cli --power package --native . -o gh-puller -f \
  --maintainer "Oto Brglez"
```

## Resources
- https://tech.ovoenergy.com/scala-native-webserver/
- https://www.baeldung.com/scala/native-apps-scala-native
- https://typelevel.org/blog/2022/09/19/typelevel-native.html

[libcurl]: https://curl.se/libcurl/
[nix-shell]: https://nixos.org/manual/nix/stable/command-ref/nix-shell.html
[scala-cli]: https://scala-cli.virtuslab.org/
