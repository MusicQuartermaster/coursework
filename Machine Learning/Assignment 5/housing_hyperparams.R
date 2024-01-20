FLAGS= flags( 
    flag_numeric("learning_rate", 0.01),
    flag_numeric("units1", 32),
    flag_numeric("units2", 32),
    flag_numeric("batch_size", 32),
    flag_numeric("dropout1", 0.2),
    flag_numeric("dropout2", 0.2)
  )

library(keras)
ann <- keras_model_sequential() %>%
  layer_dense(units=FLAGS$units1, input_shape=ncol(train.nzv), activation=FLAGS$activation_function) %>%
  layer_dropout(FLAGS$dropout1) %>%
  layer_dense(units=FLAGS$units2, activation=FLAGS$activation_function) %>%
  layer_dropout(FLAGS$dropout2) %>%
  layer_dense(units=1, activation="relu")

history <- ann %>% compile( loss="mse", optimizer=optimizer_adam(learning_rate=FLAGS$learning_rate), metric=c("mae") )
ann %>% fit(as.matrix(train.nzv), as.matrix(train.labels/100000), epochs = 30, batch_size=FLAGS$batch_size, validation_data=list(val, val.labels/100000), verbose=2)