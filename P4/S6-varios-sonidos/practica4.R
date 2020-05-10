library(tuneR)
library(seewave)
#library(soundgen)
library(audio)

# establecer el path concreto en cada caso a la carpeta de trabajo
setwd("C:/Users/migue/Downloads/S6-varios-sonidos/S6-varios-sonidos")

# cargamos los archivos de audio y mostramos informacion 
# de cada uno de ellos
perro <- readWave('perro.wav')
perro
gato  <- readMP3('gato.mp3')
gato

# tambine podemos ver solamente la duracion del sonido de cada audio
# haciendo un redondeo con 3 decimales
round(length(perro@left) / perro@samp.rate, 3)
round(length(gato@left) / gato@samp.rate, 3)

# mostrar los campos del archivo de sonido
str(perro)
str(gato)

# reproducimos ambos sonidos, cada uno con su rate
f <- gato@samp.rate    
listen(gato,f=f)

f <- perro@samp.rate
listen(perro,f=f)

# dibujamos la forma de la onda de ambos sonidos
plot( extractWave(gato, from = 1, to = 393984) )
plot( extractWave(perro, from = 1, to = 159732) )

# le uno al audio del perro el del gato
s <- pastew(gato, perro, output="Wave")
s
plot( extractWave(s, from = 1, to=553716) )
listen(s)

# creo un filtro Butterworth para eliminar las frecuencias por
# debajo de 3000 Hz
filtro <- bwfilter(s, f, channel = 1, n=1,from = 0, to = 3000, bandpass = TRUE, listen = TRUE, output = "Wave")
filtro
str(filtro)

# guardamos el sonido filtrado en un archivo .wave
writeWave(filtro, file.path("mezcla.wav"))

# usamos el audio del perro para crear un sonido con eco 
eco <- 1000*echo(perro, f, channel = 1, amp = c(0.8,0.4,0.2), delay = c(1,2,3), plot = TRUE,listen = TRUE, output = "Wave")
eco
str(eco)

# le damos la vuelta al sonido con eco y guardamos el sonido
# en un archivo .wave
alreves <- revw(eco, f, channel = 1, env = TRUE, ifreq = FALSE,plot = TRUE, output = "Wave")
listen(alreves)
writeWave(alreves, file.path("alreves.wav"))
