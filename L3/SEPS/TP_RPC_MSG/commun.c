#include <commun.h>

extern 
void print_cr( const cr_t cr )
{
  switch(cr)
    {
    case OK : 
      printf(" OK \n");
      break ;
    case ERR_NUM_FONC : 
      printf(" Erreur sur le numero de fonction\n");
      break ;
    case ERR_NUM_BIB : 
      printf(" Erreur sur le numero de bibliotheque\n");
      break ;
    case ERR_BIB_STRING_TR :
      printf(" Erreur de translate dans la bibliotheque de string\n");
      break ;
    case ERR_BIB_TAB_NB :
      printf(" Erreur de translate dans la bibliotheque de string\n");
      break ;
    case ERR_MSGSND :
      printf(" Erreur sur envoie d'un message\n");
      break ;
    case ERR_MSGRCV :
      printf(" Erreur sur reception d'un message\n");
      break ;
    default : 
      printf(" Numero de cr inconnu %d\n" , cr );
      break;
     }
}
