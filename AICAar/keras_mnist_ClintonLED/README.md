```
pip3 install keras
```
## Makefile
Provided Makefile describes various targets that help with the above mentioned tasks.


### make train
Train and save Keras MNIST model if Keras model files are not found.

### make run
Run the program

model.json `Only contain model graph (Keras Format)`.

weights.h5 `Only contain model weights (Keras Format)`.

model.h5 `Both contain model graph and weights (Keras Format)`.

