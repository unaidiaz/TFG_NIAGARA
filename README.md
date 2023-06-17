# TFG_NIAGARA

## Descripcion:

Los sistemas de partículas son un elemento muy importante de los videojuegos que aportan realismo e inmersión al jugador, estas, combinadas con efectos de postproducción, aportan detalles y completan la escena visualmente para que no parezca que falta algo o que la escena está vacía , no solo son importantes a nivel visual, también hay mecánicas que pueden basarse en este tipo de simulaciones.

El problema que presentan este tipo de simulaciones es que si se pretende conseguir resultados muy realistas, estas requieren de un gran cálculo de físicas y de renderizado que afectan al rendimiento general del juego, por lo tanto, es importante encontrar un sistema que consiga un punto medio que combine un buen resultado que sea creíble para el jugador, con una buena optimización que no afecte drásticamente al rendimiento del juego.   
Para desarrollar este sistema se van a crear dos sistemas de partículas diferentes, una que simula de manera físicamente realista una simulación de humo con un renderizado de densidad realista, usando técnicas de Ray Tracing y de guardado en caché de la simulación para mayor optimización.

Por otra parte, el otro sistema estará más enfocado a la optimización, pensado para que afecte lo menos posible al rendimiento, pero también pensado para conseguir resultados que sean completamente creíbles para el jugador, este último sistema estará pensado para ser usado como los sistemas de partículas de Unity o Unreal, que dan más flexibilidad para crear todo tipo de sistemas.

El objetivo será comparar rendimientos y resultados de ambos sistemas para determinar cuál es más óptimo para ser usado en un contexto de real time y cuál es más apropiado para ser usado en un contexto donde los tiempos de cálculos no son tan relevantes como puede ser la industria cinematográfica.

![sistema de particulas 1](Capturas/par-1.png)
![sistema de particulas 2](Capturas/par-2.png)