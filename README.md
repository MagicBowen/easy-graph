
## Easy Graph


### TODO

- [ ]: assert visitor and dsl
- [ ]: node attributes
- [ ]: user defined edge type and attributes
- [ ]: readme && usage

### layout

```sh
cpan install Graph::Easy
```

```sh
echo "[a]->[b]->[c]->[d][b]->{ start: right, 0; }[e],[d]"|graph-easy
```

- http://bloodgate.com/perl/graph/manual/
- https://metacpan.org/pod/Graph::Easy

### Cli Usage

```sh
$ chmod a+x ./ccup.sh

# start project from docker env
# make sure docker is pre-installed on the system.
./ccup.sh -e

# update depends and execute cmake generating
./ccup.sh -u

# build
./ccup.sh -b

# update & build
./ccup.sh -ub

# run tests
./ccup.sh -t

# build & test
./ccup.sh -bt

# update & build & test
./ccup.sh -ubt

# run executable
./ccup.sh -r

# install
./ccup.sh -i

# build & install
./ccup.sh -bi

# update & build & install
./ccup.sh -ubi

# clean build
./ccup.sh -c

# clean all
./ccup.sh -C

# help
./ccup.sh -h
```
