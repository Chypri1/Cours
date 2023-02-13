public class Liste{

	Object o;
	Liste suite;

	Liste(){
		this.o = null;
		this.suite = null;
	}

	void addFirst(Object o){
		if(this.o == null) this.o = o;
		else{
			Liste l = new Liste();
			l.o = this.o;
			l.suite = this.suite;
			this.o = o;
			this.suite = l;
		}
	}

	void addLast(Object o){
		if(this.o == null) this.o = o;
		else{
			if(this.suite == null){
				Liste l = new Liste();
				l.o = o;
				this.suite = l;
			}
			else this.suite.addLast(o);
		}
	}

	// renvoie -1 si o n'existe pas, les indices commencent à 0
	int index(Object o){
		if(this.o.equals(o)) return 0;
		else{
			if(this.suite == null) return -1;
			else return 1+this.suite.index(o);
		}
	}

	// renvoie le ieme caractere ou null s'il y a moins de i objets dans la liste
	Object get(int i){
		if(i==0){
			return this.o;
		}
		else{
			if(this.suite != null) return this.suite.get(i-1);
			else return null;
		}
	}

	// retourne vrai si l'element existe, faux sinon
	boolean remove(Object o){
		int pos = this.index(o);
		if(pos!=-1){
			Liste l = this;
			for(int i=0;i<pos-1;i++) l = l.suite;
			l.suite = l.suite.suite;
			return true;
		}
		else return false;
	}

	int size(){
		if(this.suite == null){
			if(this.o == null) return 0;
			else return 1;
		}
		else return 1+this.suite.size();
	}

	public String toString(){
		if(this.o==null) return "";
		else{
			String s = this.o.toString();
			if(this.suite!=null) s = s + " , " + this.suite.toString();
			return s;
		}
	}

	static String randomString(int length){
		char[] t = new char[length];
		for(int i=0;i<length;i++) t[i] = (char) ('a'+(int) (Math.random()*26));
		return new String(t);
	}

	public static void main(String[] toto){
		/*Liste l = new Liste();
		for(int i=0;i<20;i++) l.addLast(randomString(5));
		for(int i=0;i<20;i++) System.out.println(l.get(i));*/
		Liste l = new Liste();
		for(int j=0;j<3;j++){
			Liste lj = new Liste();
			for(int i=0;i<20;i++) lj.addLast(randomString(5));
			l.addLast(lj);
		}
		for(int i=0;i<l.size();i++){
			Liste lj = (Liste) l.get(i);
			for(int j=0;j<lj.size();j++) System.out.println(lj.get(j));
			System.out.println("****");
		}
	}
}
