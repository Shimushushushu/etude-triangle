# etude-triangle-cuda

This is a replica of `etude-triangle-cpu` except that it is written in cuda in order to speed up.

The main code is in `etude-triangle-cuda/main.c` , which is commented, except `[^1]`. See the corresponding appendix in the `README.md` of `etude-triangle-cpu` for details.

## Testing Environment:

- Ubuntu 18.04.5 LTS
- Unknown CPU
- Unknown RAM
- NVIDIA GeForce GTX 1080 Ti
- ```
  nvcc: NVIDIA (R) Cuda compiler driver
  Built on Wed_Oct_23_19:24:38_PDT_2019
  Cuda compilation tools, release 10.2, V10.2.89
  ```
- `nvcc etude-triangle-cuda/main.c -o main`

## Testing Result:

```
duration: 0.0262620ms
```