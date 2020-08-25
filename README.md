### Feature Obliviator

This Tripal 3 module provides a drush command that allows
users to delete data from the `chado.feature` table by
specifying the organism and the analysis for which features
should be deleted.

### Installation

Clone to `DRUPAL_ROOT/sites/all/modules` then enable the module using drush en feature_obliviator.

### Usage

Simply run the command and follow the prompts.
```bash
drush obliviate
```

You will be asked to select an organism from the list. Once selected, you
will be presented with a list of analyses to select from. The module will
then confirm the number of features to be deleted and allow you to delete
them.

### License

This open source module is licensed under MIT.

Copyright 2020 University of Tennessee Knoxville. All rights reserved.