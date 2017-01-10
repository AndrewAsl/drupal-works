<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Prepare a simple form to add an entry, with all the textfielderesting fields.
 */
function calcmet_form_addkvadrat($form, &$form_state) {
  $form = array();
  
  $form['kvadratdata'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Данные по квадратам'),
  );
  $form['kvadratdata']['storona'] = array(
    '#type'  => 'textfield',
    '#title' => t('Cторона квадрата (а), мм'),
    '#size'  => 60,
  );
  $form['kvadratdata']['kvcsa'] = array(
    '#type'  => 'textfield',
    '#title' => t('Площадь поперечного сечения, см2'),
    '#size'  => 60,
  );
  $form['kvadratdata']['kvmassonem'] = array(
    '#type'  => 'textfield',
    '#title' => t('Масса 1 м, кг'),
    '#size'  => 60,
  );  
  $form['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Add'),
  );
  return $form;
}

function calcmet_form_addkvadrat_submit($form, &$form_state) {  
  // Save the submitted entry.
  //dsm($form_state);  
  $basename = 'calcmetkvadrat';
  if(!empty($form_state['values']['storona'] && $form_state['values']['kvcsa'] && $form_state['values']['kvmassonem'])){
      $entry = array(
        'ccid'  => 4,  
        'cucid'  => 0,  
        'storona' => $form_state['values']['storona'],
        'kvcsa' => $form_state['values']['kvcsa'],
        'kvmassonem' => $form_state['values']['kvmassonem'], 
      );
  } else {
      drupal_set_message ('Введите данные');
  }   
  $return = calcmet_entry_insert ($basename, $entry);
  if ($return) {
    drupal_set_message(t("Created entry @entry", array('@entry' => print_r($entry, TRUE))));
  }
}