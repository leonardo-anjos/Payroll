#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Folha_Pagamento{
	
	char nome[50];
	float sal;	//salario
	int hed;	//horas extras diurnas
	int hen;	//horas extras noturnas
	int num_dep;	//número de dependentes
	int fal;	//faltas em horas
	float descont;	//descontos eventuais
	float ref;	//gastos com refeições feitas na empresa
	float vale;	//vales retirados durante o mês
}pg;

void Saida(int emissoes, pg pg[100]){
	
	char url[]="Folha de Pagamento.txt";
	float folha;
	
	FILE *arq;
	
	//arqivo = fopen("folha_de_pagamento.txt", "w");
	arq = fopen(url, "w");
	
	if(arq == NULL){
		printf("ERROR!\n");
		exit(0);
	}else{
			int i;
			for(i=0; i<emissoes; i++)
			{	
				fprintf(arq, "\tDADOS DO FUNCIONARIO\n");
				fprintf(arq, "----------------------------\n");
				fprintf(arq, "Nome: %s\n",strupr(pg[i].nome));	//exibir o nome do funcinario em caixa alta
	
				fprintf(arq, "Cargo: ANALISTA DE SEGURANÇA DA INFORMAÇÃO\n");	//cargo
	
				fprintf(arq, "Salario: R$%.2f\n\n", pg[i].sal);	//salario
	
				//calculo das horas extras trabalhadas
				//(hed * sal) + ((hen * 1.2 * sal) / 160)
				float he = (((pg[i].hed) * (pg[i].sal)/160) + ((pg[i].hen) * 1.2 *(pg[i].sal)/160));
				fprintf(arq, "Hora(s) Extra(s): R$%.2f\n", he);
	
				//calculo do auxilio salario familia (abono)
				//num_dep * 0.05 * salario minimo vigente
				float sal_familia = ((pg[i].num_dep)* 0.05 * 880.00);
				fprintf(arq, "Salario Familia: R$%.2f\n", sal_familia);
	
				//salario bruto
				//sal + he(hen + hed) + sal_familia(abono)
				float sb = ((pg[i].sal) + he + sal_familia);
				fprintf(arq, "Salario Bruto: R$%.2f\n", sb);
	
				//////////////////////////////////////////////////////////////////////////////////
	
				fprintf(arq, "\n\n\tDESCONTOS EFETUADOS\n");
				fprintf(arq, "---------------------------\n");
	
	//Instituto Nacional do Seguro Social
	//Atenção: O valor máximo do INSS do segurado empregado é R$ 513,01 
	/*
		Para os empresarios também esta disponivel uma tabela 
		que regularmenta as taxas de renda conforme categorias
		
		* Empresario - 11%
		* Autonomos(PF) - 20%
		* Autonomos(PJ) - 11%
		* Individuais e Facultativos - 11%
	*/
				float inss;
				if(inss <= 1556.94){
					inss = 0.08 * (pg[i].sal);
					fprintf(arq, "INSS: R$%.2f\n", inss);
				}else{
					if((inss >= 1556.95) && (inss <= 2594.92)){
						inss = 0.09 * (pg[i].sal);
						fprintf(arq, "INSS: R$%.2f\n", inss);
					}else{
						if((inss >= 2594.93) && (inss <= 5189.82))
							inss = 0.11 * (pg[i].sal);
							fprintf(arq, "INSS: R$%.2f\n", inss);
						}
					}
					
				//calculo de imposto de renda (base de calculo mensal)
				float irpf;
				if(sb <= 1787.77){
					fprintf(arq, "IRPF: Isento\n");
				}else{
					if((sb > 1787.77) && (sb <= 2679.29)){
						irpf = 0.075 * sb;
						fprintf(arq, "IRPF: R$%.2f\n", irpf);
					}else{
						if((sb >= 2679.30) && (sb <= 3572.43)){
							irpf = 0.15 * sb;
							fprintf(arq, "IRPF: R$%.2f\n", irpf);
						}else{
							if((sb >= 3572.44) && (sb <= 4463.81)){
								irpf = 0.225 * sb;
								fprintf(arq, "IRPF: R$%.2f\n", irpf);
							}else{
								if(sb >= 4463.82){
									irpf = 0.275 * sb;
									fprintf(arq, "IRPF: R$%.2f\n", irpf);
								}
							}
						}
					}
				}	
	
				//calculo de desconto sobre as faltas
				//(fal * sal)/160
				float faltas = ((pg[i].fal)*(pg[i].sal)/160);
				fprintf(arq, "falta(s): %.2f\n", faltas);
	
				//descontos sobre refeicoes
				fprintf(arq, "Refeicoes: R$%.2f\n", pg[i].ref);

				//descontos sobre vale	
				fprintf(arq, "Vales: R$%.2f\n", pg[i].vale);
	
				fprintf(arq, "Descontos Enventuais: R$%.2f\n", pg[i].descont);
		
				//calculos de descontos totais
				//inss + faltas + refeicao + vales + descontos + irpf
				float desconto_total = (inss + (pg[i].fal) + (pg[i].ref) + (pg[i].vale) + (pg[i].descont) + irpf);
				fprintf(arq, "Descontos Totais: R$%.2f\n", desconto_total);
				
				//calculo de salario liquido = salario_bruto - desconto_total
				float salario_liquido = sb - desconto_total;
				fprintf(arq, "\n\nSalario liquido: R$%.2f\n", salario_liquido);
			}
		}
			fclose(arq);
}

/*void Saida(int emissoes, pg pg[100]){	//funcao para exibicao da folha de pagamento
	
			system("color 17"); 
		system("cls");  
	
		int i;
	for(i=0; i<emissoes; i++)
	{
		printf("\tDADOS DO FUNCIONARIO\n");
		printf("-----------------------------\n");
		printf("%s\n",strupr(pg[i].nome));	//exibir o nome do funcinario em caixa alta
	
	printf("DIRETOR DE SEGURANCA DA INFORMACAO\n");	//cargo
	
	printf("Salario: R$%.2f\n", pg[i].sal);	//salario
	
		//calculo das horas extras trabalhadas
		//(hed * sal) + ((hen * 1.2 * sal) / 160)
	float he = ((pg[i].hed)*(pg[i].sal)/160 + (pg[i].hen)*1.2*(pg[i].sal)/160);
	printf("Hora(s) Extra(s): R$%.2f\n", he);
	
		//calculo do auxilio salario familia (abono)
		//num_dep * 0.05 * salario minimo vigente
	float sal_familia = ((pg[i].num_dep)*0.05*880);
	printf("Salario Familia: R$%.2f\n", sal_familia);
	
		//salario bruto
		//sal + he(hen + hed) + sal_familia(abono)
	float sb = ((pg[i].sal) + he + sal_familia);
	printf("Salario Bruto: R$%.2f\n", sb);
	
	//////////////////////////////////////////////////////////////////////////////////
	
	printf("\n\n\tDESCONTOS EFETUADOS\n");
	printf("---------------------------\n");
	
		//Instituto Nacional do Seguro Social 
		//0.08 * sal
	float inss = 0.08 * (pg[i].sal); 
	printf("INSS: R$%.2f\n", inss);
	
		//calculo de desconto sobre as faltas
		//(fal * sal)/160
	float faltas = ((pg[i].fal)*(pg[i].sal)/160);
	printf("falta(s) = %.2f\n", faltas);
	
		//descontos sobre refeicoes
	printf("Refeicoes: R$%.2f\n", pg[i].ref);

		//descontos sobre vale	
	printf("Vales: R$%.2f\n", pg[i].vale);
	
	printf("Descontos Enventuais: R$%.2f\n", pg[i].descont);
	 
	 	//calculo de imposto de renda (base de calculo mensal)
	float irpf;
	if(sb <= 1787.77){
		printf("IRPF: Isento\n");
	}else{
		if((sb > 1787.77) && (sb <= 2679.29)){
			irpf = 0.075 * sb;
			printf("IRPF: R$%.2f\n", irpf);
		}else{
			if((sb >= 2679.30) && (sb <= 3572.43)){
				irpf = 0.15 * sb;
				printf("IRPF: R$%.2f\n", irpf);
			}else{
				if((sb >= 3572.44) && (sb <= 4463.81)){
					irpf = 0.225 * sb;
					printf("IRPF: R$%.2f\n", irpf);
				}else{
					if(sb >= 4463.82){
						irpf = 0.275 * sb;
						printf("IRPF: R$%.2f\n", irpf);
					}
				}
			}
		}
	}
		
		//calculos de descontos totais
		//faltas + descontos + refeicao + vale
	float desconto_total = faltas + (pg[i].descont) + (pg[i].ref) + (pg[i].vale);
	
		//calculo de salario liquido
		//salario_bruto - desconto_total
	float salario_liquido = sb - desconto_total;
	printf("\n\nSalario liquido: R$%.2f\n", salario_liquido);
	}
}*/

void Entrada(int emissoes, pg pg[100]){	//funcao para o preenchimento dos dados de funcionarios
	
	//Deseja-se fazer a emissão da folha de pagamento de uma empresa. 
	//Para cada um dos n funcionários da empresa são dadas as seguintes informações:
	
		system("color 17");  
	
		int i;
	for(i=0; i<emissoes; i++)
	{
			system("cls");	//limpa a tela
		printf("\n\t\tDADOS DO FUNCIONARIO\n");
		printf("------------------------------------\n\n");
			
			fflush(stdin);
		printf("Nome: ");
		gets(pg[i].nome);
		
			fflush(stdin);
		printf("Salario: ");
		scanf("%f", &pg[i].sal);
		
		printf("Horas extras diurnas: ");
		scanf("%d", &pg[i].hed);
		
		printf("Horas extras noturnas: ");
		scanf("%d", &pg[i].hen);
	
		printf("Numero de dependentes: ");
		scanf("%d", &pg[i].num_dep);
	
		printf("Faltas em horas: ");
		scanf("%d", &pg[i].fal);
	
		printf("Descontos eventuais: ");
		scanf("%f", &pg[i].descont);
		
		printf("Gastos com refeicoes na empresa: ");
		scanf("%f", &pg[i].ref);
	
		printf("Vales retirados durante o mes: ");
		scanf("%f", &pg[i].vale);
		
			system("cls");	
		printf("FOLHA EMITIDA COM SUCESSO!");
		
		Saida(emissoes, pg);	//chama a funcao para exibir os resultados
	}
}

int main(){
	
	pg pg[100];

		system("color 2F");
	printf("TRABALHO DE ALGEBRA LINEAR\n");
	printf("--------------------------\n");
	printf("FOLHA DE PAGAMENTO 2.0\n\n");
	
	int emissoes;
	
	printf("Digite a quantidade de folhas que deseja emitir: ");	//qtd de emissoes de folhas de pagamentos
	scanf("%d", &emissoes);
	
	Entrada(emissoes, pg);
	
	return 0;
}
