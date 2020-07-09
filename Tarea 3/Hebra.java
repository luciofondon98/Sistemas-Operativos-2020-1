import java.util.Scanner; 

public class Hebra extends Thread {
    static int mayor_divisor = 1;
    private int inicio;
    private int final_;

    public Hebra (int inicio, int final_){
        this.inicio = inicio;
        this.final_ = final_;
    }
    
    public void run(){
		int mayor_cant_divisores = 1, divisores_i;
		for (int i = inicio; i <= final_; i++){
			divisores_i = 0;
			for (int j = 2; j <= i; j++){
				if (i % j == 0){
					divisores_i = divisores_i + 1;
				}
			}
			if (divisores_i > mayor_cant_divisores){
				mayor_cant_divisores = divisores_i;
				mayor_divisor = i;
			}
		}
    }
    public static void main(String[] args) {
        System.out.println("Ingrese un entero positivo mayor o igual a 1: ");
		Scanner scan = new Scanner(System.in);
        int N = scan.nextInt();
        scan.close();
         
        final long startTime = System.nanoTime();
        int cant_hebras = 64; 
        Hebra arreglo_hebras[] = new Hebra[cant_hebras]; //Hacemos un arreglo de hebras
        int inicio = 1, final_ = N/cant_hebras;
        for (int i = 0; i < cant_hebras; i++) {
            arreglo_hebras[i] = new Hebra(inicio, final_);
            arreglo_hebras[i].start(); //Inicializamos cada hebra
            inicio = final_ + 1;
            final_= final_ + N/cant_hebras;
        }
        
        for (Hebra t : arreglo_hebras) //Recorremos todas las hebras del arreglo
            try {
                t.join(); //Esperamos a que las hebras mueran

            } catch (Exception e) {
                    System.out.println("Hubo un error");
            }     

        final long endTime = System.nanoTime();
        long totalTime = endTime - startTime;
        System.out.println("El número con la mayor cantidad de divisores entre 1 y " + N + " es: " + mayor_divisor);
		System.out.println("El tiempo que toma en ejecutarse el programa en segundos es de: " + totalTime/1000000000f + " segundos.");
    }
}