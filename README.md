# gh-puller

App that pulls events from Github "Events" API endpoints.

## Development

The easies way to get started with this project is to install [`nix-shell`] and then install [scala-cli] and other dependencies, such as `libcurl` with it.

```bash
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
