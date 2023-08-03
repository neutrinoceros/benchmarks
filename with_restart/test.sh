set -euxo pipefail

idfx conf -mpi -gpu
idfx run --nproc 8 --tstop 0.52
idfx run --nproc 8 -restart
idfx digest --all -o report.json
