## Easy Graph

`Easy graph` is a C + + library, which supports the description of graph topology and attributes through DSL. 
It also supports the display of graph to command line terminal through `Graph::Easy` module of perl. 
In addition, it supports the modification and assertion of graph structure.

The design goal of `easy graph` is to make it easy for anyone to expand.

### Graph DSL

See `example/example.cc` for DSL usage.

### Graph Modify

Preview usage of graph modifier by `test/feature_test/graph_modify_test.cc`.

### Graph Assertion

Preview usage of graph asertion by  `test/feature_test/graph_assert_test.cc`.

### Graph Layout

Preview usage of graph layout by  `test/feature_test/graph_layout_test.cc`.

The graph layout function needs to pre install `Graph::Easy` module of perl.

```sh
# install Graph::Easy by cpan which pre-installed in Ubuntu or MacOS
cpan install Graph::Easy
```

```sh
# test graph-easy
echo "[a]->[b]->[c]->[d][b]->{ start: right, 0; }[e],[d]" | graph-easy
```

Usage of `Graph::Easy` of perl in reference section.

### Core Design

The design of `easy graph` makes it very easy for anyone to extend functions for it.

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
