public class Crypteur{
    Liste alphabet;
    Liste alphabet_decale;

    Crypteur(int deca){
        alphabet_decale=new Liste();
        alphabet=new Liste();
  char c1 = 'a';
    char c2 = (char)('a' + deca);

    for(int i = 0 ; i < 26 ; i++){
      alphabet.addLast(c1);
      alphabet_decale.addLast(c2);
      c1 = (char)(c1+1);
      c2 = (char)(c2+1);

    /*remise à 'a' car nous sommes en UTF-8*/
      if(c2 > 'z'){
        c2 = 'a';
      }
    }
  }

  
    String encrypt (String message){
        char[] message_crypt= new char[message.length()];
        int indice;
        for(int i=0;i<message.length();i++){
            if(message.charAt(i) >= 'a' && message.charAt(i) <= 'z'){
            indice=this.alphabet.index(message.charAt(i));
            message_crypt[i]=(char) this.alphabet_decale.get(indice);
            /*S'il y a des espaces*/
            }
            else if(message.charAt(i) == ' ')
                message_crypt[i] = message.charAt(i);
      
        }
        String crypt = new String(message_crypt);
        return crypt;
    }


    public static void main(String arg[]){
        int i;
        Crypteur crypt1= new Crypteur(3);
        System.out.println("alphabet classique: ");
        System.out.println(crypt1.alphabet.toString());
        System.out.println(crypt1.encrypt("zx sx"));


    }


}