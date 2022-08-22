#include<stdio.h>
#include<string.h>
#include <locale.h>
#include <stdlib.h>


typedef struct sAluno
{
    int prontuario;
    char nome[60];
    char curso[5];
    int status;
};

typedef struct sLivro
{
    int tombo;
    char titulo[60];
    char autor[60];
    int ano;
    char sit;
    int status;
};

typedef struct sEmprestimo
{
    int dia;
    int mes;
    int dia_dev;
    int mes_dev;
    int livro;
    int aluno;
    char sit; /// F - Finalizado | P - Pendente
};

// FUNÇÃO INCLUIR, ALTERAR, APRESENTAR, EXCLUSAO LÓGICA EXCLUSAO FISICA

struct sAluno ler_aluno ()
{

    struct sAluno aluno;

    printf("Digite prontiario: ");
    scanf("%d", &aluno.prontuario);


    printf("Digite nome: ");
    fflush(stdin);
    gets(aluno.nome);

    printf("Digite o curso: ");
    fflush(stdin);
    gets(aluno.curso);




    aluno.status = 1;


    return aluno;

};



void incluir_aluno()
{

    struct sAluno aluno;


    FILE *arquivo;

    arquivo = fopen("dados_aluno.dat", "ab");

    if(arquivo == NULL)
    {
        arquivo = fopen("dados_aluno", "wb");

        if (arquivo == NULL)
        {
            printf("Arquivo não foi criado.");

            exit(0);
        }
    }

    aluno = ler_aluno();

    fwrite(&aluno, sizeof(struct sAluno), 1, arquivo);

    fclose(arquivo);


}

void imprime_aluno(struct sAluno aluno)
{

    if(aluno.status)
    {
        printf("\nProntuario:%d\n", aluno.prontuario);
        printf("Nome:%s\n", aluno.nome);
        printf("Curso:%s\n", aluno.curso);
        printf("Status:%d\n\n", aluno.status);
    }
}

void apresenta_aluno()
{

    struct sAluno aluno;

    FILE *arquivo;

    arquivo = fopen("dados_aluno.dat", "rb");

    if(arquivo == NULL)
    {
        printf("Arquivo não foi lido.");

    }

    else
    {
        fread(&aluno, sizeof(struct sAluno), 1, arquivo);

        while(!feof(arquivo))
        {
            imprime_aluno(aluno);
            fread(&aluno, sizeof(struct sAluno), 1, arquivo);

        }


    }

    fclose(arquivo);

}

int localiza_aluno(int pront)
{
    int posicao=-1;
    int i=0;

    FILE *arquivo;
    struct sAluno aluno;
    arquivo = fopen("dados_aluno.dat", "rb");

    if(arquivo == NULL)
    {
        printf("Arquivo não encontrato.");
    }

    else
    {
        fread(&aluno, sizeof(struct sAluno), 1, arquivo);

        while(!feof(arquivo)&& posicao==-1)
        {
            if(aluno.prontuario == pront)
            {
                posicao=i;
            }

            fread(&aluno, sizeof(struct sAluno), 1, arquivo);

            i++;
        }
    }

    fclose(arquivo);
    return posicao;

}

int subcresver_aluno(struct sAluno aluno, int posicao)
{
    int total;

    FILE *arquivo;
    arquivo = fopen("dados_aluno.dat", "rb+");

    if(arquivo == NULL)
    {
        printf("Arquivo não encontrato.");
    }

    else
    {
        fseek(arquivo, 0, SEEK_END);
        total=ftell(arquivo)/sizeof(struct sAluno);
        if (posicao < total)
        {
            fseek(arquivo, posicao*sizeof(struct sAluno),SEEK_SET);

            fwrite(&aluno, sizeof(struct sAluno), 1, arquivo);

        }
        else
        {
            printf("Não existe esta posição no arquivo.");


        }

        fclose(arquivo);
        return 1;
    }

}

void alterar_aluno()
{

    struct sAluno aluno;

    int prontuario, posicao;


    printf("Digite o prontuario do aluno a ser alterado:");
    scanf("%d", &prontuario);

    posicao = localiza_aluno(prontuario);

    if (posicao == -1)
    {
        printf("Este prontuario nao existe.\n");
    }

    else
    {
        aluno = ler_aluno(posicao);

        if( subcresver_aluno(aluno, posicao) == 0)
        {
            printf("Não foi possivel fazer a alteração.\n");
        }

        else
        {
            printf("Dados alterados.\n");

        }
    }


}

void excluir_aluno()
{
    int pront;
    int pos;
    struct sAluno aluno;

    printf("Qual prontuario voce deseja excluir: ");
    scanf("%d",&pront);

    pos = localiza_aluno(pront);

    if(pos == -1)
    {
        printf("aluno não encontrado.\n");

    }
    else
    {
        printf("deseja excluir o aluno \n0 - sim \n1 - nao\n");
        scanf("%d",&aluno.status);

        if(subcresver_aluno(aluno,pos) == 0)
        {
            printf("ja excluido\n");
        }
        else
        {
            printf("excluido com sucesso\n");
        }

    }
}

void pesquisar_aluno()
{
    FILE * arquivo;
    struct sAluno aluno;
    int prontuario;
    int posicao;
    arquivo = fopen("dados_aluno.dat", "rb");

    if(arquivo == NULL)
    {
        printf("Arquivo não encontrato.");
    }
    else{
    printf("Digite o prontuario do aluno a ser pesquisado:");
    scanf("%d", &prontuario);

    posicao = localiza_aluno(prontuario);

    if (posicao == -1)
    {
        printf("Este prontuario nao existe.\n");
    }
    else{
         fseek(arquivo,posicao*sizeof(struct sAluno),SEEK_SET);

         fread(&aluno, sizeof(struct sAluno), 1, arquivo);

        while(!feof(arquivo))
        {
            imprime_aluno(aluno);
            fread(&aluno, sizeof(struct sAluno), 1, arquivo);

        }

    }
    }
    fclose(arquivo);
}

struct sLivro ler_livro()
{
    struct sLivro livro;

    printf("\nDigite o tombo:\n");
    scanf("%d",&livro.tombo);
    fflush(stdin);

    printf("Digite nome do titulo:\n");
    gets(livro.titulo);
    fflush(stdin);

    printf("Digite o nome do autor:\n");
    gets(livro.autor);
    fflush(stdin);

    printf("digite o ano do livro:\n");
    scanf("%d",&livro.ano);

    livro.sit='d';

    livro.status=1;

    return livro;

}

void incluir_livro()
{

    struct sLivro livro;


    FILE *arquivo;

    arquivo = fopen("dados_livro.dat", "ab");

    if(arquivo == NULL)
    {
        arquivo = fopen("dados_livro", "wb");

        if (arquivo == NULL)
        {
            printf("Arquivo não foi criado.");

            exit(0);
        }
    }

    livro = ler_livro();

    fwrite(&livro, sizeof(struct sLivro), 1, arquivo);

    fclose(arquivo);


}
void listar_livros()
{
    struct sLivro livro;

    FILE *arquivo;

    arquivo = fopen("dados_livro.dat", "rb");

    if(arquivo == NULL)
    {
        printf("Arquivo não foi lido.");

    }

    else
    {
        fread(&livro, sizeof(struct sLivro), 1, arquivo);

        while(!feof(arquivo))
        {
            imprime_livro(livro);
            fread(&livro, sizeof(struct sLivro), 1, arquivo);

        }


    }

    fclose(arquivo);

}

void imprime_livro(struct sLivro livro)
{
        if(livro.status)
    {
        printf("\nTombo:%d\n", livro.tombo);
        printf("\nTitulo:%s\n", livro.titulo);
        printf("Autor:%s\n", livro.autor);
        printf("Ano:%d\n", livro.ano);
        printf("Situação:%c\n\n", livro.sit);
    }
}

void alterar_livro()
{
    struct sLivro livro;

    int tombo, posicao;


    printf("Digite o tombo do livro a ser alterado:");
    scanf("%d", &tombo);

    posicao = localiza_livro(tombo);

    if (posicao == -1)
    {
        printf("Este tombo nao existe.\n");
    }

    else
    {
        livro = ler_livro(tombo);

        if( sobrescrever_livro(livro, posicao) == 0)
        {
            printf("Não foi possivel fazer a alteração.\n");
        }

        else
        {
            printf("Dados alterados.\n");

        }
    }


}

int sobrescrever_livro(struct sLivro livro, int posicao)
{
    int total;

    FILE *arquivo;
    arquivo = fopen("dados_livro.dat", "rb+");

    if(arquivo == NULL)
    {
        printf("Arquivo não encontrato.");
    }

    else
    {
        fseek(arquivo, 0, SEEK_END);
        total=ftell(arquivo)/sizeof(struct sLivro);
        if (posicao < total)
        {
            fseek(arquivo, posicao*sizeof(struct sLivro),SEEK_SET);

            fwrite(&livro, sizeof(struct sLivro), 1, arquivo);

        }
        else
        {
            printf("Não existe esta posição no arquivo.");


        }

        fclose(arquivo);
        return 1;
    }

}

int localiza_livro(int tombo)
{
    int posicao=-1;
    int i=0;

    FILE *arquivo;
    struct sLivro livro;
    arquivo = fopen("dados_livro.dat", "rb");

    if(arquivo == NULL)
    {
        printf("Arquivo não encontrato.");
    }

    else
    {
        fread(&livro, sizeof(struct sLivro), 1, arquivo);

        while(!feof(arquivo)&& posicao==-1)
        {
            if(livro.tombo == tombo)
            {
                posicao=i;
            }

            fread(&livro, sizeof(struct sLivro), 1, arquivo);

            i++;
        }
    }

    fclose(arquivo);
    return posicao;

}

void excluir_livro()
{
    int tombo;
    int pos;
    struct sLivro livro;

    printf("Tombo do livro que deseja excluir: ");
    scanf("%d",&tombo);

    pos = localiza_livro(tombo);

    if(pos == -1)
    {
        printf("livro não encontrado.\n");

    }
    else
    {
        printf("deseja excluir o Livro: \n0 - sim \n1 - nao\n");
        scanf("%d",&livro.status);

        if(sobrescrever_livro(livro,pos) == 0)
        {
            printf("ja excluido\n");
        }
        else
        {
            printf("excluido com sucesso\n");
        }

    }
}

void pesquisar_livro()
{
    FILE * arquivo;
    struct sLivro livro;
    int tombo;
    int posicao;
    arquivo = fopen("dados_livro.dat", "rb");

    if(arquivo == NULL)
    {
        printf("Arquivo não encontrato.");
    }
    else{
    printf("Digite o tombo do livro a ser pesquisado:");
    scanf("%d", &tombo);

    posicao = localiza_livro(tombo);

    if (posicao == -1)
    {
        printf("Este livro nao existe.\n");
    }
    else{
         fseek(arquivo,posicao*sizeof(struct sLivro),SEEK_SET);

         fread(&livro, sizeof(struct sLivro), 1, arquivo);

        while(!feof(arquivo))
        {
            imprime_livro(livro);
            fread(&livro, sizeof(struct sLivro), 1, arquivo);

        }

    }
    }
    fclose(arquivo);
}

struct sEmprestimo ler_emprestimo ()
{

    struct sEmprestimo emp;
    struct sLivro livro;
    int prontuario;
    int tombo;
    int cond, conddia, condmes, condtombo;
    int pos;

    printf("Digite seu prontuário:\n");
    scanf("%d",&prontuario);

    cond=localiza_aluno(prontuario);

    if(cond==-1)
    {
        printf("prontuário inválido\n");
    }
    else{
      emp.aluno=prontuario;
       printf("Informe o dia:");
       scanf("%d",&conddia);
       if(conddia < 1 || conddia > 30)
       {
           printf("Dia inválido\n");
       }
       else{

        emp.dia=conddia;
        emp.dia_dev = calcula_devolucao_dia(emp.dia);
        printf("digite o mês:");
        scanf("%d",&condmes);
        if(condmes < 1 || condmes > 12)
        {
            printf("Mês inválido");
        }else{
            emp.mes=condmes;
            emp.mes_dev = calcula_devolucao_mes(emp.dia, emp.dia_dev, emp.mes);
            printf("Digite o tombo do livro:");
            scanf("%d",&condtombo);
            tombo = localiza_livro(condtombo);
            if(tombo == -1)
            {
                printf("Livro inválido");
            }
            else{
            emp.livro=tombo;

            pos = localiza_livro(emp.livro);



    }
    } } }
     emp.sit='e';

return emp;
}

int calcula_devolucao_dia(int dia)
{
    dia+=7;
    if(dia > 30)
        return dia - 30;
    return dia;
}

int calcula_devolucao_mes(int dia_old, int dia_new, int mes)
{
    if(dia_old > dia_new)
        if(mes+1 > 12)
            return 1;
        else
            return mes+1;
    return mes;
}

void incluir_emp()
{

    struct sEmprestimo emp;


    FILE *arquivo;

    arquivo = fopen("dados_emprestimos.dat", "ab");

    if(arquivo == NULL)
    {
        arquivo = fopen("dados_emprestimos", "wb");

        if (arquivo == NULL)
        {
            printf("Arquivo não foi criado.");

            exit(0);
        }
    }

    emp = ler_emprestimo();

    fwrite(&emp, sizeof(struct sEmprestimo), 1, arquivo);

    fclose(arquivo);

}

void main()
{
    setlocale(LC_ALL, "Portuguese");
    int controle;
    do
    {
        printf( "\n/-----------------------------------------------------------/\n\n" );
        printf(" Menu:\n"                                                             );
        printf(" [1] Incluir Aluno\n"                                                 );
        printf(" [2] Listar Alunos\n"                                                 );
        printf(" [3] Alterar Aluno\n"                                                 );
        printf(" [4] Excluir Aluno\n"                                                 );
        printf(" [5] Pesquisar Aluno\n"                                               );
        printf(" [6] Incluir Livro\n"                                                 );
        printf(" [7] Listar Livros\n"                                                 );
        printf(" [8] Alterar Livro\n"                                                 );
        printf(" [9] Excluir Livro\n"                                                 );
        printf(" [10] Pesquisar Livro\n"                                              );
        printf(" [11] Realizar emprestimo\n"                                          );
        printf(" [0] Sair\n"                                                          );
        printf( "\n /-----------------------------------------------------------/\n"  );
        printf("Opção:");
        scanf("%d", &controle);
        system("cls");

        switch(controle)
        {
        case 1:
            incluir_aluno();
            break;

        case 2:
            apresenta_aluno();
            break;

        case 3 :
            alterar_aluno();
            break;

        case 4:
            excluir_aluno();
            break;

        case 5:
            pesquisar_aluno();
            break;

        case 6:
            incluir_livro();
            break;

        case 7:
            listar_livros();
            break;

        case 8:
            alterar_livro();
            break;

        case 9:
            excluir_livro();
            break;

        case 10:
            pesquisar_livro();
            break;

        case 11:
           incluir_emp();
            break;

        case 12:

            break;
        }

         system("pause");
        getch();
        system("cls");

    }
    while(controle != 0);

}

