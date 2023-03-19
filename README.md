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

## Notes

- Scala Native compilation can be a bit slow. To speedup the development process I've wrote a [curl_requests.c](./curl_requests.c) in pair with [curl_requests_test.c](./curl_requests_test.c). Meaning that you can compile and run your C code independently of Scala (Native) build process.
- The [curl_requests.c](./curl_requests.c) code is likely "leaky" as it doesen't release memory after the "c strings" are returned from C code to Scala context. Additional work is needed to get that goin'

## Resources
- https://tech.ovoenergy.com/scala-native-webserver/
- https://www.baeldung.com/scala/native-apps-scala-native
- https://typelevel.org/blog/2022/09/19/typelevel-native.html

[libcurl]: https://curl.se/libcurl/
[nix-shell]: https://nixos.org/manual/nix/stable/command-ref/nix-shell.html
[scala-cli]: https://scala-cli.virtuslab.org/
