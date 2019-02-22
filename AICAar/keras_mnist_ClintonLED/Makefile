
TF_MODEL_FOLDER = TF_Model/
MODEL_FILENAME = TF_Model/tf_model.meta
CONV_SCRIPT = ./convert-mnist.py
RUN_SCRIPT = ./predict-mnist-keras-cam.py
TRAIN_SCRIPT = ./train-mnist.py
INPUT_NODE_FLAG = -in=conv2d_1_input
OUTPUT_NODE_FLAG = -on=dense_2/Softmax
KERAS_WEIGHT_FILE = weights.h5
KERAS_MODEL_JSON_FILE = model.json

.PHONY: run
run: compile
	python3 ${RUN_SCRIPT}
.PHONY: train
train:
	(test -f ${KERAS_WEIGHT_FILE} && test -f ${KERAS_MODEL_JSON_FILE}) || python3 ${TRAIN_SCRIPT}
	@echo "Training finished. \
	If you want to retrain the model, delete '${KERAS_WEIGHT_FILE}' and '${KERAS_MODEL_JSON_FILE}' files."

  
