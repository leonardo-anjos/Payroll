Exercícios com Matrizes
INSTITUTO DE MATEMATICA E ESTATSTICA - IME USP

12.  (FEA 68) Deseja-se fazer a emissão da folha de pagamento de uma empresa. Para cada um dos n funcionários da empresa são dadas as seguintes informações:

    NOME
    SAL (salário)
    HED (horas extras diurnas)
    HEN (horas extras noturnas)
    ND (número de dependentes)
    FAL (faltas em horas)
    DE (descontos eventuais)
    REF (gastos com refeições feitas na empresa)
    VAL (vales retirados durante o mês).

Emitir as seguintes informações:

    nome,
    salário,
    horas extras = HED * SAL/160 + HEN * 1.2 * SAL/160,
    salário família = ND * 0.05 * salário mínimo vigente,
    salário bruto = salário + horas extras + salário família.

Descontos efetuados:

    INAMPS = 0.08 * SAL,
    faltas = FAL * SAL/160,
    refeições,
    vales,
    descontos eventuais,
    imposto de renda = 0.08 * salário bruto.

Salário líquido = salário bruto - desconto total. 
