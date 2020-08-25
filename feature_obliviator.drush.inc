<?php

/**
 * @return array
 */
function feature_obliviator_drush_command()
{
    $commands = [];

    $commands['obliviate'] = [
        'description' => 'Get a listing of organisms and analyses to obliviate features for.',
        'examples' => [
            'drush obliviate' => 'Get a listing of organisms and analyses to obliviate features for.',
        ],
        'callback' => 'drush_feature_obliviator_obliviate'
    ];

    return $commands;
}

/**
 * @return int
 * @throws \Exception
 */
function drush_feature_obliviator_obliviate()
{
    if (! drush_confirm("You will be presented with a list of organisms to select from. Once an organism is selected, you will be presented with a list of analyses that are related to the selected organism. Once both are chosen, you will be able to delete all features related to the selected options. Continue?")) {
        return 0;
    }

    $organisms = feature_obliviator_get_organisms();
    $options = [];
    $indexed_organisms = [];
    foreach ($organisms as $organism) {
        $options[$organism->organism_id] = "{$organism->genus} {$organism->species} ({$organism->name})";
        $indexed_organisms[$organism->organism_id] = $organism;
    }

    $choice = drush_choice($options, 'Select an organism.');

    if ($choice === false) {
        return 0;
    }
    $organism = $indexed_organisms[$choice];
    $org_name = "{$organism->genus} {$organism->species} ({$organism->name})";

    $analyses = feature_obliviator_get_analyses($organism);
    $options = [];
    $indexed_analyses = [];
    foreach ($analyses as $analysis) {
        $options[$analysis->analysis_id] = $analysis->name;
        $indexed_analyses[$analysis->analysis_id] = $analysis;
    }

    $choice = drush_choice($options, 'Select an analysis.');

    if ($choice === false) {
        return 0;
    }
    $analysis = $indexed_analyses[$choice];

    drush_print("Calculating... Please wait!");
    $count = feature_obliviator_get_count($organism, $analysis);
    if(!drush_confirm("Delete $count features associated with \"$org_name\" and \"$analysis->name\"?")) {
        return 0;
    }

    $num_deleted = feature_obliviator_obliviate($organism, $analysis);
    drush_print("$num_deleted features deleted.");

    return 0;
}