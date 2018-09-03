#   0 Linha 1: alfabeto de entrada
#   1 Linha 2: alfabeto da fita
#   2 Linha 3: simbolo que representa um espaco em branco na fita
#   3 Linha 4: estado inicial
#   4 Linha 5, coloquem uma linha indicando o conjunto de estados de aceitacao
#   5 Linhas 6 em diante: transicoes, uma por linha, no formato
#   estado atual, simbolo atual,  novo estado, novo simbolo, direcao para mover a cabeca


class reader(object):
    def __init__(self, nomeArq):

        self.arq = open("{}".format(nomeArq), "r")
        buff = self.arq.read()
        linhas = buff.splitlines()

        self.AlfabetoEntrada = linhas[0]
        self.AlfabetoFita = linhas[1]
        self.EspacoBrancoFita = linhas[2]
        self.EstadosIniciais = linhas[3]
        self.EstadoAceitacao = linhas[4].split(" ")
        #self.QF = int(linhas[5])

        transicoes = linhas[-1].split(" ")
        n = self.QF = (len(transicoes)-2) // 3

        if self.QF != n:
            print("OXE?!")

        transicoes = linhas[6:]
        self.Transicoes = []
        # 1, n... , 1 , n... , n...
        for t in transicoes:
            ax = t.split(" ")
            #print (ax)
            unit = [ax[0], ax[1+n]]
            sf = []
            psf = []
            dire = []
            if n == 1:
                self.Transicoes.append([ax[0], ax[1], ax[2], ax[3], ax[4]])
            else:
                for i in range(n):
                    sf.append(ax[1+i])
                    psf.append(ax[2+n+i])
                    dire.append(ax[2+(2*n)+i])
                self.Transicoes.append([unit[0], sf, unit[1], psf, dire])

    def getAlfabetoEntrada(self):
        return self.AlfabetoEntrada

    def getAlfabetoFita(self):
        return self.AlfabetoFita

    def getEspacoBrancoFita(self):
        return self.EspacoBrancoFita

    def getEstadoInicial(self):
        return self.EstadosIniciais

    def getEstadoAceitacao(self):
        return self.EstadoAceitacao

    def getTransicoes(self):
        return self.Transicoes

    def getQuantidadeDeFitas(self):
        return self.QF
