# https://arma.sourceforge.net/faq.html#linking

win32-msvc2013 {
# armadillo < version 10
include(armadillo-blas-lapack.pri)
message("armadillo: blas lapack")
} else {
# armadillo >= version 10
include(armadillo-openblas.pri)
message("armadillo: openblas")
}
