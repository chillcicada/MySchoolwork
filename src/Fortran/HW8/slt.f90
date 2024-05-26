module slt
  use mpi
  implicit none
  integer rank, size, ierr, sendbuf, recvbuf, recvmsg
  integer status(MPI_STATUS_SIZE)

contains
  subroutine relay(rank)
    integer sendbuf, recvbuf, rank

    if (rank ==  0) then
      sendbuf = 0
      call MPI_SEND(sendbuf, 1, MPI_INTEGER, rank + 1, 1, MPI_COMM_WORLD, ierr)
      print *, 'Rank', rank, 'send ', sendbuf, ' to', rank + 1
      call MPI_RECV(recvbuf, 1, MPI_INTEGER, size - 1, 1, MPI_COMM_WORLD, status, ierr)
      print *, 'Rank', rank, 'receive ', recvbuf, ' from', size - 1
    else if (rank == size - 1) then
      call MPI_RECV(recvbuf, 1, MPI_INTEGER, rank - 1, 1, MPI_COMM_WORLD, status,ierr)
      print *, 'Rank', rank, 'receive ', recvbuf, ' from', rank - 1
      call MPI_SEND(recvbuf, 1, MPI_INTEGER, 0, 1, MPI_COMM_WORLD, ierr)
      print *, 'Rank', rank, 'send', recvbuf, ' to', 0
    else
      call MPI_RECV(recvbuf, 1, MPI_INTEGER, rank - 1, 1, MPI_COMM_WORLD, status, ierr)
      print *, 'Rank', rank, 'receive ', recvbuf, ' from', rank - 1
      call MPI_SEND(recvbuf, 1, MPI_INTEGER, rank + 1, 1, MPI_COMM_WORLD, ierr)
      print *, 'Rank', rank, 'send ', recvbuf, ' to', rank + 1
    end if
  end subroutine relay

  subroutine greet(rank)
    character(len=5) recvmsg
    integer rank, count1, count2

    do count1 = 0, size - 1
      if (count1 /= rank) then
        call MPI_SEND("hello", 5, MPI_CHARACTER, count1, 2, MPI_COMM_WORLD, ierr)
        print *, 'Rank', rank, 'sent ', 'hello', ' to', count1
      endif
    end do
    do count2 = 0, size - 1
      if (count2 /= rank) then
        call MPI_RECV(recvmsg, 5, MPI_CHARACTER, count2, 2, MPI_COMM_WORLD,status, ierr)
        print *, 'Rank', rank, 'receive ', recvmsg, ' from', count2
      end if
    end do
  end subroutine greet
end module

program main
  use slt
  use mpi

  call MPI_INIT(ierr)
  call MPI_COMM_RANK(MPI_COMM_WORLD, rank, ierr)
  call MPI_COMM_SIZE(MPI_COMM_WORLD, size, ierr)

  call relay(rank)
  call greet(rank)

  call MPI_FINALIZE(ierr)
end program main
