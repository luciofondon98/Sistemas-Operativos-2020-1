import java.util.Scanner; 

public class Parte1{
	public static void main(String[] args){
		System.out.println("Ingrese un entero positivo mayor o igual a 1: ");
		Scanner scan = new Scanner(System.in);
		int N = scan.nextInt();
		int mayor_divisor = 1, mayor_cant_divisores = 1;
		scan.close();
		final long startTime = System.nanoTime();
		for (int i = 2; i <= N; i++){
			int divisores_i = 0;
			for (int j = 2; j < i; j++){
				if (i % j == 0){
					divisores_i = divisores_i + 1;
				}
			}
			if (divisores_i > mayor_cant_divisores){
				mayor_cant_divisores = divisores_i;
				mayor_divisor = i;
			}
		}
		System.out.println("El número con la mayor cantidad de divisores entre 1 y " + N + " es: " + mayor_divisor);
		final long endTime = System.nanoTime();
		long totalTime = endTime - startTime;
		System.out.println("El tiempo que toma en ejecutarse el programa en segundos es de: " + totalTime/1000000000f + " segundos.");
	}
}

  