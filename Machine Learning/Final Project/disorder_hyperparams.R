FLAGS= flags(
    flag_numeric("learning_rate", 0.01)
   ,flag_numeric("units1", 32)
   ,flag_numeric("units2", 32)
   ,flag_numeric("batch_size", 32)
   ,flag_numeric("dropout1", 0.2)
   ,flag_numeric("dropout2", 0.2)
   ,flag_numeric("epochs", 10)
   ,flag_string("activation_function", "sigmoid")
  )

library(keras)
inputUnits = ncol(train.x)
model <- keras_model_sequential() %>%
  layer_dense(units=FLAGS$units1, input_shape=inputUnits, activation=FLAGS$activation_function) %>%
  layer_dropout(FLAGS$dropout1) %>%
  layer_dense(units=FLAGS$units2, activation=FLAGS$activation_function) %>%
  layer_dropout(FLAGS$dropout2) %>%
  layer_dense(units=9, activation="softmax")

history <- model %>% compile( loss="sparse_categorical_crossentropy", optimizer=optimizer_adam(learning_rate=FLAGS$learning_rate), metric=c("accuracy") )
model %>% fit(as.matrix(train.x), as.matrix(train.y), epochs = FLAGS$epochs, batch_size=FLAGS$batch_size, validation_data=list(val, val.labels), verbose=2)