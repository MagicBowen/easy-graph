
## Easy Graph

Easy graph is a C++ library for describing graph topology and attributes by DSL;
It support layouting the graph in console by `Graph-Easy` module of perl;
It also support to modify or assert the graph topology and attributes.

### Graph DSL

See `example/example.cc` for usage.

### Graph Modify

See `test/feature_test/graph_modify_test.cc` for usage.

### Graph Assertion

See `test/feature_test/graph_assert_test.cc` for usage.

### Graph Layout

See `test/feature_test/graph_layout_test.cc` for usage.

Graph layout feature needs `Graph::Easy` module of perl pre-installed.

```sh
# install Graph::Easy by cpan which pre-installed in Ubuntu or MacOS
cpan install Graph::Easy
```

```sh
# test graph-easy
echo "[a]->[b]->[c]->[d][b]->{ start: right, 0; }[e],[d]" | graph-easy
```

Usage of `Graph::Easy` module of perl in reference section;

### Core Design

Core design of `easy graph`:

![](docs/images/model.png)

### Cli Usage

`easy graph` used ccup cli for building and testing:

```sh
$ chmod a+x ./ccup.sh

# help
./ccup.sh -h

# update dependencies
# cmake generating
./ccup.sh -u

# build
./ccup.sh -b

# update & build
./ccup.sh -ub

# run example
./ccup.sh -r

# run tests
./ccup.sh -t

# build & test
./ccup.sh -bt

# update & build & test
./ccup.sh -ubt

# clean build
./ccup.sh -c

# clean all
./ccup.sh -C
```
### Reference

- [Graph::Easy manual](http://bloodgate.com/perl/graph/manual/)
- [Graph::Easy apis](https://metacpan.org/pod/Graph::Easy)