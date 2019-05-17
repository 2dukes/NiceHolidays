	Este programa denominado NiceHolidays, com um total de cerca de 3 mil linhas de c�digo tem como prop�sito, simular um software de gest�o de uma ag�ncia de viagens.
Relativamente ao modelo utilizado, podemos dizer que seguimos a sketch proposta inicialmente. No entanto, fizemos algumas altera��es. Certas coisas achamos desnecess�rias, outras adicionamos. 
De uma forma geral, a nossa principal preocupa��o foi sempre manter a otimiza��o. Na quest�o dos pacotes, procuramos n�o ter de replicar informa��o. 
Refirmo-nos ao facto de termos um vector<Packet> na Class Agency e outro vector<Packet> na Class Client. Desta forma, substitu�mos o segundo por um vector<Packet*>, pelas raz�es anteriormente explicadas.
H� cerca de um dia atr�s, descobrimos que quando cri�vamos novos pacotes, dando push_back para o vector<Packet> da Agency, haveria a possibilidade de esse mesmo vetor ter de ser realocado. 
Desta forma, o nosso vector<Packet*> iria apontar para locais agora desconhecidos. Esse foi o �nico problema que surgiu de uma forma mais inesperada. 
Pensamos em v�rias solu��es:
-> Fazer resize do vector<Packet> para um n�mero suficientemente grande <- Alto custo no desempenho
-> Reapontar os pointers do vector<Packet*>... Ter�amos de voltar a ler o clients.txt <- M�dio custo no desempenho
-> Substituir o vector<Packet> da Agency por vector<Packet*> onde os pacotes eram todos gerados por aloca��o din�mica de mem�ria <- Melhor solu��o! - Confirmado pelo professor JAS (17/05/2019)!
-> Dar reserve do vector<Packet> <- M�dio custo no desempenho

Uma vez que est�vamos j� numa fase avan�ada do projeto, optamos pela �ltima solu��o, mesmo tendo a consci�ncia de que n�o era a mais indicada.
Fora esse percal�o, tudo correu bem e pensamos estar de acordo com que � suposto o programa fazer.

Foi um projeto deveras desafiante e trabalhoso, mas bem conseguido!
