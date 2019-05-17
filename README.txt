	Este programa denominado NiceHolidays, com um total de cerca de 3 mil linhas de código tem como propósito, simular um software de gestão de uma agência de viagens.
Relativamente ao modelo utilizado, podemos dizer que seguimos a sketch proposta inicialmente. No entanto, fizemos algumas alterações. Certas coisas achamos desnecessárias, outras adicionamos. 
De uma forma geral, a nossa principal preocupação foi sempre manter a otimização. Na questão dos pacotes, procuramos não ter de replicar informação. 
Refirmo-nos ao facto de termos um vector<Packet> na Class Agency e outro vector<Packet> na Class Client. Desta forma, substituímos o segundo por um vector<Packet*>, pelas razões anteriormente explicadas.
Há cerca de um dia atrás, descobrimos que quando criávamos novos pacotes, dando push_back para o vector<Packet> da Agency, haveria a possibilidade de esse mesmo vetor ter de ser realocado. 
Desta forma, o nosso vector<Packet*> iria apontar para locais agora desconhecidos. Esse foi o único problema que surgiu de uma forma mais inesperada. 
Pensamos em várias soluções:
-> Fazer resize do vector<Packet> para um número suficientemente grande <- Alto custo no desempenho
-> Reapontar os pointers do vector<Packet*>... Teríamos de voltar a ler o clients.txt <- Médio custo no desempenho
-> Substituir o vector<Packet> da Agency por vector<Packet*> onde os pacotes eram todos gerados por alocação dinâmica de memória <- Melhor solução! - Confirmado pelo professor JAS (17/05/2019)!
-> Dar reserve do vector<Packet> <- Médio custo no desempenho

Uma vez que estávamos já numa fase avançada do projeto, optamos pela última solução, mesmo tendo a consciência de que não era a mais indicada.
Fora esse percalço, tudo correu bem e pensamos estar de acordo com que é suposto o programa fazer.

Foi um projeto deveras desafiante e trabalhoso, mas bem conseguido!
