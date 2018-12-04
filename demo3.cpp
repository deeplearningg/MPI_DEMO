/**
 * 输出一个进程的两个“进程号”：
 * - 在操作系统中的进程号；
 * - 在MPI环境中，某一通信器中的进程号。
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <mpi.h>

int
main (int argc, char *argv[])
{
  int myrank, myrank_1, nprocs;

  // 初始化MPI环境
  MPI_Init (&argc, &argv);

  // 每个进程都获取它在通信器“MPI_COMM_WORLD”中的进程号
  //MPI_COMM_WORLD全大写，是通信器名称。
  MPI_Comm_rank (MPI_COMM_WORLD, &myrank);

  // 每个进程都获取它在通信器“MPI_COMM_SELF”中的进程号
  MPI_Comm_rank (MPI_COMM_SELF, &myrank_1);

  // 每个进程都获取通信器“MPI_COMM_WORLD”中的进程总数
  MPI_Comm_size (MPI_COMM_WORLD, &nprocs);
//tderr -- 标准错误输出设备 ，不用深究这东西，mpi格式化打印语句，使用fprintf时照着往上打就行了。getpid（）获取进程的识别码。
  fprintf (stderr, "process id = %d, myrank in MPI_COMM_WORLD = %d, myrank in MPI_COMM_SELF = %d\n", getpid (), myrank, myrank_1);

  // 结束MPI环境
  MPI_Finalize ();
  return 0;
}
