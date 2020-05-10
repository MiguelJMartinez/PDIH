
# install.packages('tuneR', dep=TRUE)
# install.packages('seewave', dep=TRUE)
# install.packages('soundgen', dep=TRUE)

library(tuneR)
library(seewave)
#library(soundgen)
library(audio)

# establecer el path concreto en cada caso a la carpeta de trabajo
setwd("C:/Users/migue/Downloads/S6-varios-sonidos/S6-varios-sonidos")
# cargar reproductor en Windows
setWavPlayer("C:/Program Files/Windows Media Player/wmplayer.exe")

# cargar archivos de sonido (wav/mp3):
perro <- readWave('perro.wav')
perro
oveja <- readWave('oveja.wav')
oveja
gato  <- readMP3('gato.mp3')
gato

# mostrar los campos del archivo de sonido
str(oveja)
str(gato)

# calcular la duración exacta del sonido (con tres decimales)
round(length(gato@left) / gato@samp.rate, 3)


f <- gato@samp.rate    #44100

# escuchar un sonido:
listen(gato,f=f)

# mostrar la onda del sonido:
plot( extractWave(gato, from = 1, to = 393984) )


# escuchar una porción del sonido original:
listen(gato, f=f, from=6.5, to=8.9)


# cortar segmentos de un objeto “wave”:
s2 <- cutw(gato, from=6.5,to=8.9, output="Wave")
s2
plot( extractWave(s2, from = 1, to = 105841) )
listen(s2)


# añadir segmentos:
s3 <- pastew(perro, s2, output="Wave")
s3
plot( extractWave(s3, from = 1, to=265573) )
listen(s3)


# eliminar segmentos de sonido:
s4 <- deletew(s3, output="Wave", from = duration(s2), to = duration(perro))
duration(s4)
s4
plot( extractWave(s4, from = 1, to=211681) )
listen(s4)


# escribir el sonido en un archivo WAV:
writeWave(s4, file.path("snd-gato-perro.wav") )


# extraer un canal y crear un sonido mono:
sndObjLeft <- mono(gato, "left")
str(sndObjLeft)
sndObjLeft

listen(sndObjLeft,f=f)

plot( extractWave(sndObjLeft, from = 1, to = 393984) )

writeWave(sndObjLeft, file.path("tmpSndLeft.wav") )
