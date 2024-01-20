FLAGS= flags( 
    flag_numeric("learning_rate", 0.01),
    flag_numeric("units1", 32),
    flag_numeric("units2", 32),
    flag_numeric("batch_size", 32),
    flag_string("activation_function", "relu")
  
  )

library(keras)
model <- keras_model_sequential() %>%
  layer_dense(units=FLAGS$units1, input_shape=5000, activation=FLAGS$activation_function) %>%
  layer_dense(units=FLAGS$units2, activation=FLAGS$activation_function) %>%
  layer_dense(units=3, activation="softmax")

history <- model %>% compile( loss="sparse_categorical_crossentropy", optimizer=optimizer_adam(learning_rate=FLAGS$learning_rate), metric="accuracy" )
model %>% fit (covid.train.dtm.norm, covid.train$Sentiment, epochs=20, batch_size=FLAGS$batch_size, validation_data=val, verbose=2)