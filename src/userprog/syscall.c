#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "devices/shutdown.h"
#include "threads/vaddr.h"

/* User process's Program ID - default to int */
typedef int pid_t;

static void syscall_handler (struct intr_frame *);

/* Added methods */
void *check_address( const void * );
static void     system_exit_user_prog ( int status );
/*static pid_t    system_run_executable ( const char *cmd_line );
static int      wait_till_process_exit ( pid_t pid );
static bool     system_created_file ( const char *file, unsigned initial_size );
static bool     system_deleted_file ( const char *file );
static int      system_open_file ( const char *file );
static int      file_size_bytes ( int fd );
static int      file_bytes_read ( int fd, void *buffer, unsigned size );*/
/*static int      file_bytes_write ( int fd, const void *buffer, unsigned size );*/
/*static void     seek_file_position ( int fd, unsigned position );
static unsigned next_file_position ( int fd );*/
static void     close_file ( int fd );

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f) 
{
  int *virt_addr_sp = f->esp;

  /* now reduce the pointer to an integer constant */
  int which_system_call = *virt_addr_sp;

  /* Checks for invalid user pointer */
  check_address( virt_addr_sp );


  switch ( which_system_call )
  {
    case SYS_HALT:
    /* Terminates Pintos by calling shutdown_power_off(), 
       declared in devices/shutdown.c */
    shutdown_power_off();
    break;

    case SYS_EXIT:
    check_address( virt_addr_sp + 1 );
    system_exit_user_prog( *(virt_addr_sp + 1) );
    break;

    case SYS_EXEC:
    /*system_run_executable( );*/
    break;

    case SYS_WAIT:
    /*wait_till_process_exit( );*/
    break;

    case SYS_CREATE:
    /*system_created_file( );*/
    break;

    case SYS_REMOVE:
    /*system_deleted_file( );*/
    break;

    case SYS_OPEN:
    /*system_open_file( );*/
    break;

    case SYS_FILESIZE:
    /*file_size_bytes( );*/
    break;

    case SYS_READ:
    /*file_bytes_read( );*/
    break;

    case SYS_WRITE:
    /*file_bytes_write( *(virt_addr_sp + 1), 
                      *(virt_addr_sp + 2), 
                      *(virt_addr_sp + 3) );*/
    break;

    case SYS_SEEK:
    /*seek_file_position( );*/
    break;
    
    case SYS_TELL:
    /*next_file_position( );*/
    break;
    
    case SYS_CLOSE:
    /*close_file( );*/
    break;

  }//End switch - which system call

  return ;
}


/* Checks to make sure the given virtual address is in the 
   user memory and not the kernel memory. */
void  
*check_address ( const void *virt_address )
{
  if( is_kernel_vaddr(virt_address) )
  {
    system_exit_user_prog( -1 );
    return 0;
  }

  void *addr_pointer = pagedir_get_page( thread_current()->pagedir, virt_address );
  if( addr_pointer == NULL )
  {
    system_exit_user_prog( -1 );
    return 0;
  }
}


/* Terminates the current user program. Returns a status to the kernel */
static void 
system_exit_user_prog ( int status )
{
  struct thread *current_t = thread_current();
  struct list_elem *list_parser;

  /*while( !list_empty(&current_t->thread_file_list) )
  {
    list_parser = listbegin( &current_t->thread_file_list );
    close_file( list_entry( list_parser, struct user_prog_file, file_list_elem )->fid );
  }*/

  current_t->return_status = status;
  thread_exit();
}


/* Runs the executable with the name given in 'cmd_line'.
   Returns the new process's program id (pid) */
/*static pid_t 
system_run_executable ( const char *cmd_line UNUSED )
{
  return;
}*/


/* If the process 'pid' is still alive, we wait until it dies. 
   Returns the status that pid was passed to System_exit_user_prog(), or -1 */
/*static int 
wait_till_process_exit ( pid_t pid UNUSED )
{
  return 0;
}*/


/* Creates a new file called 'file' with initial byte size of 'initial_size'
   Returns true if success, false otherwise */
/*static bool 
system_created_file ( const char *file UNUSED, unsigned initial_size UNUSED )
{
  return true;
}*/


/* Deletes the file called 'file'. Can delete files that are open.
   Deleting an open file does not close it. 
   Returns true if success, false otherwise */
/*static bool 
system_deleted_file ( const char *file UNUSED )
{
  return true;
}*/


/* Opens the file called 'file'. Returns a file descriptor (fd) if
   success or -1 if the file couldn't be opened. each open returns
   a new file descriptor. */
/*static int 
system_open_file ( const char *file UNUSED )
{
  return 0;
}*/


/* Returns the size in bytes of the file opened with fd, 'fd' */
/*static int 
file_size_bytes ( int fd UNUSED )
{
  return 0;
}*/


/* Reads 'size' bytes from the file opened with fd, 'fd' into buffer.
   Returns the number of bytes actually read (0 at end of file)
   -1 if the file could not be read.
   fd 0 reads from the keyboard using input_getc() */
/*static int 
file_bytes_read ( int fd UNUSED, void *buffer UNUSED, unsigned size UNUSED )
{
  return 0;
}*/


/* Writes 'size' bytes from buffer into the open file with fd, 'fd'.
   Returns the number of bytes actually written (0 if no bytes were written) 
   fd 1 writes to the console. */
/*static int 
file_bytes_write ( int fd UNUSED, const void *buffer UNUSED, unsigned size )
{
  if( fd == 0 )*/ /* write was called with input file descriptor */
  /*{
    return -1;
  }
  else if( fd == 1 )*/ /* write to console */
  /*{
    putbuf( buffer, size );
    return size;
  }
  return -1;
}*/


/* Changes the next byte to be read of written in open file with fd,  'fd' to 
   position 'position' expressed in bytes from the beginning of the file. */
/*static void 
seek_file_position ( int fd UNUSED, unsigned position UNUSED )
{
  return;
}*/


/* Returns the position of the next byte to read or write to in the open 
   file with fd, 'fd' expressed in bytes from the beginning of the file. */
/*static unsigned 
next_file_position ( int fd UNUSED )
{
  return 0;
}*/


/* Closes the file with file descriptor 'fd' */
/*static void 
close_file ( int fd UNUSED )
{
  return;
}*/



