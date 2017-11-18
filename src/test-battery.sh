#!/bin/bash
DOCS_DIR='./docs'
BIN_DIR='./bin'
OUT_FILE=${DOCS_DIR}/$(date)
echo Arquivo de saída: $OUT_FILE
touch "${OUT_FILE}"

echo 'Iniciando bateria de testes... (leva em torno de 50 segundos)'
{
    # Ambiente de execução
    lsb_release -a > "${OUT_FILE}"
    printf "_____________________________________________________\n\n" >> "${OUT_FILE}"

    # Executa o teste 10 vezes
    i=1
    max=10
    for i in `seq 1 $max`
    do
        echo $((i++))a tentativa: >> "${OUT_FILE}"
        ./${BIN_DIR}/main >> "${OUT_FILE}"
        printf "_____________________________________________________\n\n" >> "${OUT_FILE}"
        sleep 5 # Dorme por 5 segundos
    done
} &> /dev/null

echo Final da bateria de testes.