/***************************************************************************
*  $MCI M?dulo de implementa??o: M?dulo de teste espec?fico
*
*  Arquivo gerado:              TESTEGRADE.C
*  Letras identificadoras:      GRA
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: cgln - Cristiane - Guilherme - Leonardo - Nath?lia
*
*  $HA Hist?rico de evolu??o:
*     Vers?o  Autor    Data     Observa??es 
*       2.00   cgln  09/09/2017 Elimina??o de c?digo duplicado, reestrutura??o,
*                               inicio da implementa??o dos scripts e testes.
*       1.00   cgln  02/10/2017 In?cio do desenvolvimento
*
*  $ED Descri??o do m?dulo
*     Este m?odulo cont?m as fun??es espec?ficas para o teste do
*     m?dulo grade de horario. Ilustra como redigir um interpretador de comandos
*     de teste espec?ficos utilizando o arcabou?o de teste para C.
*
*  $EIU Interface com o usu?rio pessoa
*     Comandos de teste espec?ficos para testar o m?dulo turma:
*
*     "=criarGrade"           - chama a fun??o GRA_CriaGradeHorario()
*     "=exibirGrade"          - chama a fun??o GRA_ExibeGradeHorario()
*     "=excluirGrade"         - chama a fun??o GRA_ExcluiGradeHorario()
*     "=inserirInfoGrade"     - chama a função GRA_InsereGradeHorario()
*     "=alterarGrade"         - chama a função GRA_AlteraGradeHorario()
***************************************************************************/
 
#include    <string.h>
#include    <stdio.h>
 
#include    "TST_ESPC.H"
 
#include    "generico.h"
#include    "lerparm.h"

#include    "disciplina.h"
#include    "turma.h"
#include    "GradeHorario.h"
#include    "lista.h"
 
/* Tabela dos nomes dos comandos de teste espec?ficos */

#define     CRIAR_GRA_CMD          "=criarGrade"
#define     INSERIR_GRA_CMD        "=inserirInfoGrade"
#define     EXIBIR_GRA_CMD         "=exibirGrade"
#define     ALT_FALTAS_GRA_CMD     "=alterarFaltasGrade"
#define     ALT_NOTA_GRA_CMD       "=alterarNotaGrade" 
#define     ELIMINANO_GRA_CMD      "=eliminaNo"  
#define     LIB_GRADE_GRA_CMD      "=liberaGrade" 
#define     EXCLUIR_GRA_CMD        "=excluirGrade"

/*****  C?digo das fun??es exportadas pelo m?dulo  *****/
 
 
/***********************************************************************
*
*  $FC Fun??o: GGRA Efetuar opera??es de teste espec?ficas para o m?dulo turma
*
*  $ED Descri??o da fun??o
*     Efetua os diversos comandos de teste espec?ficos para o m?dulo
*     grade de horario sendo testado.
*
*  $EP Par?metros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/
 
#define MAX_GRA 5
 
GradeHorario * grade[MAX_GRA] = { NULL, NULL, NULL, NULL, NULL } ;
Disciplina * disc[MAX_GRA] = { NULL, NULL, NULL, NULL, NULL } ;
Turma * tur[MAX_GRA] = { NULL, NULL, NULL, NULL, NULL } ;
InfoGradeHorario * info[MAX_GRA] = { NULL, NULL, NULL, NULL, NULL } ;

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {
 
      GRA_tpCondRet CondRetObtido ;
      GRA_tpCondRet CondRetEsperada ;
      
	  int index_gra = 0 ;
	  int index_disc = 0 ;
	  int index_tur = 0 ;
	  int index_info = 0 ;
	  int index_nota_alt = 0 ;

	  //Parametros GRADE
	  float nota1[] = {2,3,4,5} ;
	  float nota2[] = {10,10,10,10} ;
	  float nota3[] = {1,1,1,1} ;
	  float nota4[] = {5,5,15,5} ;
	  float nota5[] = {0,0,0,0} ;
	  float * notas_alt[5] = { nota1, nota2, nota3, nota4, nota5 } ;

	  int faltas ;

	  //Parametros DISCIPLINA
	  char CodDisc[8] ;
      
      int  NumLidos = -1 ;
 
      TST_tpCondRet Ret ;

	  /* Criando disciplinas e turmas para testar. */
	  DIS_gera_param( &disc[0], "Programacao II", "INF1007", 4, "Livro 1", "Ponteiros" );
	  DIS_gera_param( &disc[1], "Software Basico", "INF1018", 4, "Livro 3", "Assembly" );
	  DIS_gera_param( &disc[2], "BD1", "INF1383", 4, "Livro BD1", "Dados" );
	  DIS_gera_param( &disc[3], "Programacao Modular", "INF1301", 4, "Livro Modular", "Arcabouco" );
	  DIS_gera_param( &disc[4], "BD2", "INF1384", 4, "Livro BD2", "Dados" );

      TUR_CriaTurma( &tur[0], "3WA", 13, 15, "SEG-QUA", 25 );
	  TUR_CriaTurma( &tur[1], "3WB", 11, 13, "SEG-QUA", 30 );
	  TUR_CriaTurma( &tur[2], "3WC", 15, 17, "TER-QUI", 35 );
	  TUR_CriaTurma( &tur[3], "3WD", 17, 19, "TER-QUI", 40 );
	  TUR_CriaTurma( &tur[4], "3WE", 15, 17, "TER-QUI", 45 );
	

      /* Testar GRA Criar Grade de Horario  */
 
         if ( strcmp( ComandoTeste , CRIAR_GRA_CMD ) == 0 )
         {
 
            NumLidos = LER_LerParametros( "ii" ,
                                &index_gra, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */
 
            CondRetObtido = GRA_CriaGradeHorario ( grade + index_gra ) ;
 
            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar grade de horario." ) ;
 
         } /* fim ativa: Testar GRA Criar Grade de Horario */

		 
	  /* Testar GRA Insere Grade de Horário */
 
         else if ( strcmp( ComandoTeste , INSERIR_GRA_CMD ) == 0 )
         {
 
            NumLidos = LER_LerParametros( "iiiii" ,
                                &index_info, &index_disc, &index_tur, &index_gra, &CondRetEsperada ) ;
            if ( NumLidos != 5 )
            {
               return TST_CondRetParm ;
            } /* if */
   
            CondRetObtido = GRA_InsereGradeHorario (info[index_info], disc[index_disc], tur[index_disc], grade[index_gra]) ; 
 
            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir grade de horario." ) ;
 
         } /* fim ativa: Testar GRA Insere Grade de Horário */


	  /* Testar GRA Exibe Grade de Horário */

		 else if ( strcmp( ComandoTeste , EXIBIR_GRA_CMD) == 0 )
         {
 
            NumLidos = LER_LerParametros( "ii" ,
                                &index_gra, &CondRetEsperada) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */
 
            CondRetObtido = GRA_ExibeGradeHorario( grade[index_gra] ) ;
 
            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao exibir grade de horário." ) ;
 
         } /* fim ativa: Testar GRA Exibe Grade de Horário */
 

   	  /* Testar GRA Alterar Faltas */
 
         else if ( strcmp( ComandoTeste , ALT_FALTAS_GRA_CMD ) == 0 )
         {
 
            NumLidos = LER_LerParametros( "isii" ,
                                &index_gra, &CodDisc, &faltas, &CondRetEsperada ) ;
            if ( NumLidos != 4 )
            {
               return TST_CondRetParm ;
            } /* if */
 
            CondRetObtido = GRA_AlteraFaltas ( grade[index_gra], CodDisc, faltas ) ;
 
            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao alterar faltas." ) ;
 
         } /* fim ativa: Testar GRA Alterar Faltas */


	  /* Testar GRA Alterar Nota */

         else if ( strcmp( ComandoTeste , ALT_NOTA_GRA_CMD ) == 0 )
         {
 
            NumLidos = LER_LerParametros( "isii" ,
                                &index_gra, &CodDisc, &index_nota_alt, &CondRetEsperada ) ;
            if ( NumLidos != 4)
            {
               return TST_CondRetParm ;
            } /* if */
 
            CondRetObtido = GRA_AlteraNota ( grade[index_gra], CodDisc , notas_alt[index_nota_alt] ) ;
 
            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao alterar nota." ) ;
 
         } /* fim ativa: Testar GRA Alterar Nota */
     
		
	 /* Testar GRA Elimina No */
 
         else if ( strcmp( ComandoTeste , ELIMINANO_GRA_CMD) == 0 )
         {
 
            NumLidos = LER_LerParametros( "isi" ,
                                &index_gra, &CodDisc, &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */
 
            CondRetObtido = GRA_EliminaNo ( grade[index_gra], CodDisc ) ;
 
            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao eliminar no." ) ;
 
         } /* fim ativa: Testar GRA Elimina No */


    } /* Fim fun??o: TTUR Efetuar opera??es de teste espec?ficas para o m?dulo turma */
 
/********** Fim do m?dulo de implementa??o: M?dulo de teste espec?fico **********/