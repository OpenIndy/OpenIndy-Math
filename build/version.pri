
# get git version
git_command = "git --git-dir \"$$PWD/../.git\" --work-tree \"$$PWD\" describe --always --tags"
GIT_VERSION = $$system($$git_command)
message($$git_command)

# remove commit hash after tag name
GIT_VERSION = $$replace(GIT_VERSION, "-g"{1}\w*, )

# remove remaining hyphen
GIT_VERSION = $$replace(GIT_VERSION, "-", ".")

# remove commit hash (only if no tag has been set yet)
GIT_VERSION = $$replace(GIT_VERSION, "\b[0-9a-f]{5,40}\b", )

isEmpty(GIT_VERSION){
    message("no version")
}else{
    message($$GIT_VERSION)
    VERSION = $$GIT_VERSION
}
