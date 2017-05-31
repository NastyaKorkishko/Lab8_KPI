[![Travis-CI][travis-badge]][travis-builds]

[travis-badge]: https://travis-ci.org/NastyaKorkishko/libprogbase.svg?branch=master
[travis-builds]: https://travis-ci.org/NastyaKorkishko/libprogbase/builds

# lab8

# Laboratory work 8
### Task
TCP server which receives TCP clients' requests and connects with them using HTTP protocol.

#### Avaliable HTTP paths:
* `/` - sends json object with information about server
* `/favourites` - sends json list with favourite cities
* `/favorites?{key}={value}` - sends json sublist with websites from `/favourites` list which have field `{key}` set as `{value}`
* `/favorites/{id}` - sends json object from `/favourites` list with id set as `{id}`
* `/file` - reads `data.txt` file from `data/` dircetory, Sends json object with name of file, its size and data
* `/file/data` - sends json object with infromation about all numbers in `data.txt`
