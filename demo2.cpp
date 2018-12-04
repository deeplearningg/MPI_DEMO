/**
 * 进程0向进程1发送一个整数.
 */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 10

int main (int argc, char *argv[])
{
  int i, myrank;
  int a[N];
  MPI_Status status;

  // 初始化MPI环境
  MPI_Init (&argc, &argv);

  // 初始化数组
  for (i = 0; i < N; i++)
    {
      a[i] = -1;
    }

  // 获取当前进程在通信器MPI_COMM_WORLD中的进程号
  MPI_Comm_rank (MPI_COMM_WORLD, &myrank);

//让进程号为0的，数组中每一个元素都为100.
  if (myrank == 0)
    {
      for (i = 0; i < N; i++)
        {
          a[i] = i;
        }
      // 进程0向进程1发送一个整数
      MPI_Send (&a, N, MPI_INT, 1, 99, MPI_COMM_WORLD);
            for (i = 0; i < N; i++)
        {
          a[i] = 2*i;
        }
        MPI_Send (&a, N, MPI_INT, 2, 99, MPI_COMM_WORLD);
    }
  else if (myrank == 1)
    {
      fprintf (stderr, "myrank = %d, before recv. a[0] = %d\n", myrank, a[0]);
      // 进程1从进程0接收一个整数
      //MPI_Recv语句多了一个&status。
      MPI_Recv (&a, N, MPI_INT, 0, 99, MPI_COMM_WORLD, &status);
      fprintf (stderr, "myrank = %d, after recv. a[0] = %d\n\n", myrank, a[0]);
        for (i = 0; i < N; i++)
        {
          fprintf (stderr,"%d\t",a[i]);
        }
        printf("\n");
    }
    else{
    	fprintf (stderr, "myrank = %d, before recv. a[0] = %d\n", myrank, a[0]);
      // 进程1从进程0接收一个整数
      //MPI_Recv语句多了一个&status。
      MPI_Recv (&a, N, MPI_INT, 0, 99, MPI_COMM_WORLD, &status);
      fprintf (stderr, "myrank = %d, after recv. a[0] = %d\n\n", myrank, a[0]);
        for (i = 0; i < N; i++)
        {
          fprintf (stderr,"%d\t",a[i]);
        }
        printf("\n");
	}

  // 结束MPI环境，测试程序分配两个进程即可，多了其他进程陷入接收的等待中……
  MPI_Finalize ();
  return 0;
}
