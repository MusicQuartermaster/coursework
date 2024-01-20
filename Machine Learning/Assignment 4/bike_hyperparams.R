FLAGS= flags( 
    flag_numeric("learning_rate", 0.01),
    flag_numeric("units1", 32),
    flag_numeric("units2", 32),
    flag_numeric("batch_size", 32),
    flag_string("activation_function", "sigmoid")
  
  )

library(keras)
model <- keras_model_sequential() %>%
  layer_dense(units=FLAGS$units1, input_shape=ncol(train.x), activation=FLAGS$activation_function) %>%
  layer_dense(units=FLAGS$units2, activation=FLAGS$activation_function) %>%
  layer_dense(units=1, activation="relu")

history <- model %>% compile( loss="mse", optimizer=optimizer_adam(learning_rate=FLAGS$learning_rate), metric=c("mae") )
model %>% fit(train.x, train.y, epochs = 30, batch_size=FLAGS$batch_size, validation_data=val, verbose=2)